# RGB Blinky Keychain

<div align="center">

![RGB Blinky Keychain](https://github.com/rhitvik/RGB_Blinky_Keychain/blob/master/Images_and_Screenshots/RGB_Blinky_Keychain_Image.jpg)

<div align="left"> 

These are the blinky boards that NYU sent as the welcome gifts for the class of 2024. This RGB Blinky board features RGB breathing lights, PCB Art and doubles as a soldering practice kit. 1600 of these are manufactured in total. NYU is planning to have these boards manufactured for the class of 2025 and 2026 as well.

## Novelty of the Project
The novelty behind the project is the firmware developed for the microcontroller can generate an RGB breathing effect in a very limited space and resource-constrained ATtiny10 microcontroller. This microcontroller features 1 Kilobyte of flash memory and 32 bytes of RAM. While this microcontroller only supports only 2 PWM pins, I managed to implement a power-conscious, single-interrupt request process based HSV algorithm that worked as a State-Machine. 
Read more on Power-conscious breathing effect [here](https://www.instructables.com/id/How-to-Make-Proper-Rainbow-and-Random-Colors-With-/)

<div align="center"> 

![](https://github.com/rhitvik/RGB_Blinky_Keychain/blob/master/Images_and_Screenshots/RGB.jpg)
<div align="left"> 

## PCB Art
Monochromatic vector art is imported from any photo editing software like Adobe AI or Inkscape. This is the place where we also set the dimensions of the image we are looking to go with. We want to be sure that the bitmap extracted is negative or otherwise, the dimensions will be altered as the software only extracts the images that touch the bitmap on the extremities and not the dimensions set by us in the panel.
Once the image is exported as a jpeg, in the KiCad project file we go to the import bitmap file and calibrate the DPI labels to the values we set while exporting from the photo editing software. Again we select the negative plot while exporting the processed image as a KiCad file. This is because we obtained the inverted image in software and we will need to invert this again to obtain the positive mask profile. 

## Circuit
<div align="center"> 

![](https://github.com/rhitvik/RGB_Blinky_Keychain/blob/master/Images_and_Screenshots/Circuit.PNG "Schematic Capture")
<div align="left"> 

## Project files and Libraries
[LED Flasher Circuit](https://github.com/rhitvik/RGB_Blinky_Keychain/tree/master/Schematic_and_PCB)

## Link to Video
[![Alt text](https://github.com/rhitvik/RGB_Blinky_Keychain/blob/master/Images_and_Screenshots/RGB_Blinky_Thumbnail.jpg)](https://www.youtube.com/watch?v=NwK5qySm0T8&feature=youtu.be)

## Bill Of Materials (BOM)
[Link to the BOM](https://github.com/rhitvik/RGB_Blinky_Keychain/tree/master/BOM)

## Firmware
[Click here to view Code](https://github.com/rhitvik/RGB_Blinky_Keychain/blob/master/Code/Project_Infineon_Rev-10/main.cpp)

**Note 1: USE FUSE SETTING 0xFE AFTER UPLOADING THE CODE (this disables the Reset pin and lets it be used as GPIO)**

**Note 2: SET THE FUSE SETTINGS ONLY AFTER THE CODE IS UPLOADED OR ELSE A HIGH VOLTAGE PROGRAMMER WILL BE REQUIRED**

**Programming/Debugging Unit Used: ATMEL ICE** [Shop Here](https://www.digikey.com/product-detail/en/microchip-technology/ATATMEL-ICE/ATATMEL-ICE-ND/4753379)

## Future Plans
RGB Blinky Keychain 2.0 is currently under development which includes upgraded LEDs that emit diffused light and are more power-efficient. Also, the boards will include a custom-designed High-Voltage TPI interface that will eliminate the microcontroller's requirement to be preprogrammed by the supplier and will bring the manufacturing costs lower. Also, these new boards will have multiple options for PCB Art to choose from.

A programming board is also under development for the aforementioned custom-designed TPI interface and this programming board will be able to program 10 Blinky Keychains simultaneously and alleviate the task of mass programming the developed boards.