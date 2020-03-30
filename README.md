# RGB_Blinky_Keychain
 
![RGB Blinky Keychain](https://github.com/rhitvik/RGB_Blinky_Keychain/blob/master/Images_and_Screenshots/RGB_Blinky_Keychain_Image.jpg)

These are the blinky boards that NYU plans to include in the welcome kits for the class of 2024. These RGB Blinky board features RGB breathing lights, PCB Art and doubles as a soldering practice kit. 1600 of these are manufactured in total. NYU is also planning to have these boards manufactured for the class of 2025 as well.

## Novelty of the Project
Novelty behind the project is the firmware developed for the microcontroller can generate RGB breating effect in a very limited space and resource constrained ATtiny10 microcontroller. This miocontroller features 1 Kilobyte of flash memory and 32 bytes of RAM. While this icrocontroller only supports only 2 PWM pins, I managed to implement a power concious, single-interrupt request process based HSV alorithm that worked as a State-Machine. 

## PCB Art
Monochromatic vector art is imported from any photo editing software like Adobe AI or Inkscape. This is the place where we also set the dimensions of the image we are looking to go with. We want to be sure that the bitmap extracted is of a negative nature or otherwise the dimensions will be altered as the software only extracts the images that touches the bitmap on the extremeties and not the dimensions set by us in the panel.
Once the image is exported as a jpeg, in the KiCad project file  we go to the import bitmap file and calibrate the DPI labels to the values we set while exporitng from the photo editing software. Again we select the negative plot while exporting the procssed image as a KiCad file. This is because we obtained the inverted image in software and we will need to invert this again to obtain the positive mask profile. 

## Circuit
![](https://github.com/rhitvik/RGB_Blinky_Keychain/blob/master/Images_and_Screenshots/Circuit.PNG "Schematic Capture")

## Bill Of Materials (BOM)
[Link to the BOM](https://github.com/rhitvik/RGB_Blinky_Keychain/tree/master/BOM)

## Firmware
[Code](https://github.com/rhitvik/RGB_Blinky_Keychain/blob/master/Code/Project_Infineon_Rev-10/main.cpp)
**Note 1: USE FUSE SETTING 0xFE AFTER UPLOADING THE CODE (this disables the Reset pin and lets it to be used as GPIO)**
**Note 2: SET THE FUSE SETTINGS ONLY AFTER THE CODE IS UPLOADED OR ELSE A HIGH VOLTAGE PROGRAMMER WILL BE REQUIRED**
**Programming/Debugging Unit Used: ATMEL ICE** [Shop Here](https://www.digikey.com/product-detail/en/microchip-technology/ATATMEL-ICE/ATATMEL-ICE-ND/4753379)

## Future Plans
RGB Blinky Keychains 2.0 are currently under development which includes upgraded LEDs that emmit diffused light and are more power efficient. Also, the boards will include a costom designed High-Voltage TPI interface that will eliminate the microcontroller's requirement to be preprogrammed by the supplier and will bring the manufacturing costs lower. Also, these new boards will have a multiple options of PCB Art to choose from.

A programming board is also under development for the aforementioned custom designed TPI interface and this programming board will be able to program 10 Blinky Keychains simultaniously and alliviate the task of mass programming the developed boards.