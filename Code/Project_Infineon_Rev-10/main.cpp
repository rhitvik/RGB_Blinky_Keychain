/*
 * Project_Infineon_Rev-10.cpp
 *
 * Created: 12/26/2019 2:06:12 AM
 * Author : RHITVIK
 */ 
/*
 * Project_Infineon_Rev-9.cpp
 *
 * Created: 12/26/2019 1:01:46 AM
 * Author : RHITVIK
 */ 

/*
 * Project_Infeneon Rev-7.cpp
 *
 * Created: 11/30/2019 3:28:48 AM
 * Author : RHITVIK
 */ 

#define F_CPU	8000000UL
#define GREEN	0
#define RED		1
#define BLUE	2


#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>
#include <stdbool.h>

//		+====+
//	PB0 |*	 | PB3 (RESET)
//	GND |	 | VCC
//	PB1 |    | PB2
//		+====+

volatile uint8_t count[3] = {0,0,0};
volatile uint8_t Duty[3] = {0,100,0};
volatile bool increaseDuty[3] = {true,true,true};

volatile uint8_t MrCount = 0;
volatile uint8_t Theta = 0;
volatile uint8_t State = 1;

volatile uint8_t wait_white = 0;
volatile int count_white = 0;
volatile int Duty_white = 0;

volatile int MrCount_white = 0;
volatile bool increaseDuty_white = true;

int main(void)
{
	CCP = 0xD8;		// Unlock special consideration register
	CLKPSR = 0x00;	// Set the system clock to 8 MHz
	
	DDRB |= (1U<<PINB0) | (1U<<PINB1) | (1U<<PINB2);
	//DDRB &= ~(1U<<PINB3);
	PORTB |= (1U<<PINB0) | (1U<<PINB1) | (1U<<PINB2); //setting pins high will turnoff the RGB in common anode configuration
	//PUEB |= (1U<<PUEB3);	// Pull up on Pin B3
	
	TCCR0B |= (1U<<WGM02) | (1U<<CS00); 
	//Fast PWM mode with no Pre-Scalar Selection 
    TIMSK0 |= (1U<<OCIE0A);
	//Set Output Compare Interrupt Enable 
	
	// 8 000 000 / 10000 = 800
	OCR0AH = 800 >> 8;
	OCR0AL = 800 & 0xFF;
	
	sei();	// Enable Global Interrupts
	
	bool pressed = 0;
	bool interruptCleared = false;
	
	while (1){
		if (bit_is_clear(PINB,3))
		{
			if (pressed == 0)
			{
				pressed = 1;
				
				cli();
				interruptCleared = true;
				_delay_ms(30);			
				State = State + 1;
				State = (State >= 9)? 1:State;	
				
				count[GREEN] = 0;
				count[RED] = 0;
				count[BLUE] = 0;
				
				Duty[GREEN] = 0;
				Duty[RED] = (State == 1)? 100:0;
				Duty[BLUE] = 0;
				
				increaseDuty[GREEN] = true;
				increaseDuty[RED] = true;
				increaseDuty[BLUE] = true;

				MrCount = 0;
				Theta = 0;

				wait_white = 0;
				count_white = 0;
				Duty_white = 0;

				MrCount_white = 0;
 				increaseDuty_white = true;		
			}
		}
		else
		if(bit_is_set(PINB,3))
		{
			pressed = (pressed == 1)? 0:pressed;
			if (interruptCleared == true){
				interruptCleared = false;
				sei();
			}
		}					
    }	//while(1)
}	//int main()

ISR(TIM0_COMPA_vect){	// will be called 10,000 times every second
	//in 10000 hz we can work with a freq interval of 1000 hz
	// that is out of the 1000 times we can turn on the at a given count and ...
	// ... then turn off at a given interval
	// for example for a 50 percent duty cycle turn it on at the count of 500
	
	switch (State){
		case 1:
		///// case 1 starts here
		count[GREEN]++;
		count[RED]++;
		count[BLUE]++;
		
		MrCount++;
		if (MrCount == 255)
		{
			MrCount = 0;
			Theta++;
			Theta = (Theta > 90)? 0:Theta;
			
			switch(Theta){
				
				case 1 ... 30:
				increaseDuty[GREEN] = (increaseDuty[GREEN] == true)? increaseDuty[GREEN]:true;
				increaseDuty[RED] = (increaseDuty[RED] == false)? increaseDuty[RED]:false;
				
				Duty[GREEN] = (increaseDuty[GREEN] == true)? Duty[GREEN]+1: (Duty[GREEN] == 0)? 0:Duty[GREEN]-1;
				Duty[RED] = (increaseDuty[RED] == true)? Duty[RED]+1: (Duty[RED] == 0)? 0:Duty[RED]-1;
				Duty[BLUE] = (Duty[BLUE] == 0)? Duty[BLUE]:0;
				break;
				
				case 31 ... 60:
				increaseDuty[GREEN] = (increaseDuty[GREEN] == false)? increaseDuty[GREEN]:false;
				increaseDuty[BLUE] = (increaseDuty[BLUE] == true)? increaseDuty[BLUE]:true;
				
				Duty[GREEN] = (increaseDuty[GREEN] == true)? Duty[GREEN]+1: (Duty[GREEN] == 0)? 0:Duty[GREEN]-1;
				Duty[RED] = (Duty[RED] == 0)? Duty[RED]:0;
				Duty[BLUE] = (increaseDuty[BLUE] == true)? Duty[BLUE]+1: (Duty[BLUE] == 0)? 0:Duty[BLUE]-1;
				break;
				
				case 61 ... 90:
				increaseDuty[RED] = (increaseDuty[RED] == true)? increaseDuty[RED]:true;
				increaseDuty[BLUE] = (increaseDuty[BLUE] == false)? increaseDuty[BLUE]:false;
				
				Duty[GREEN] = (Duty[GREEN] == 0)? Duty[GREEN]:0;
				Duty[RED] = (increaseDuty[RED] == true)? Duty[RED]+1: (Duty[RED] == 0)? 0:Duty[RED]-1;
				Duty[BLUE] = (increaseDuty[BLUE] == true)? Duty[BLUE]+1: (Duty[BLUE] == 0)? 0:Duty[BLUE]-1;
				break;
			}			
		}
		
		switch (count[GREEN]){
			
			case 1 ... 99:
			if (count[GREEN] >= Duty[GREEN]){
				//turn off the pin
				PORTB |= 0x01;
			}
			break;
			
			case 100:
			count[GREEN] = 0; // set count back to 0
			//if the pin is off
			//turn
			if ( (bit_is_set(PINB,GREEN)) && (Duty[GREEN] != 0) ) {
				PORTB &= ~(1<<PINB0);
			}
			break;
			
		}
		
		switch (count[RED]){
			
			case 1 ... 99:
			if (count[RED] >= Duty[RED]){
				//turn off the pin
				PORTB |= 0x02;
			}
			break;
			
			case 100:
			count[RED] = 0; // set count back to 0
			//if the pin is off
			//turn
			if ( (bit_is_set(PINB,RED)) && (Duty[RED] != 0) ) {
				PORTB &= ~(1<<PINB1);
			}
			break;
		}
		switch (count[BLUE]){
			
			case 1 ... 99:
			if (count[BLUE] >= Duty[BLUE]){
				//turn off the pin
				PORTB |= 0x04;
			}
			break;
			
			case 100:
			count[BLUE] = 0; // set count back to 0
			//if the pin is off
			//turn
			if ( (bit_is_set(PINB,BLUE)) && (Duty[BLUE] != 0) ) {
				PORTB &= ~(1<<PINB2);
			}
			break;
			
		}
		///// case 1 ends here 
		break;
		
		case 2 ... 8:
		///// case 2 starts here
		count_white++;
		
		MrCount_white++;
		if (MrCount_white >= 255)
		{
			MrCount_white = 0;
			Duty_white = (increaseDuty_white == true)? Duty_white+1:Duty_white-1;
			
			if ((Duty_white > 30) || (Duty_white < 0)) {
				if (Duty_white > 30) { Duty_white = 30; increaseDuty_white = false;}
				else if (Duty_white < 0){
					Duty_white = 0;
					wait_white++;
					if (wait_white == 3){
						wait_white = 0;
						increaseDuty_white = true;
					}
				}
			}
			
		}
		
		switch (count_white){
			
			case 1 ... 99:
			if (count_white >= Duty_white){
				//turn off the pin
				PORTB |= 0x07;
			}
			break;
			
			case 100:
			count_white = 0; // set count back to 0
			//if the pin is off
			//turn
			if ( ((bit_is_set(PINB,0)) || (bit_is_set(PINB,1)) || (bit_is_set(PINB,2))) && (Duty_white != 0) ) {
				PORTB &= 0x06 + State;
			}
			break;
			
		}
		///// case 2 ends here
		break;

	} // switch (state)	
}
