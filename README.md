# RGB_Blinky_Keychain
 
![RGB Blinky Keychain]()

These are the blinky boards that NYU plans to include in the welcome kits for the class of 2024. These RGB Blinky board features RGB breathing lights, PCB Art and doubles as a soldering practice kit. 1600 of these are manufactured in total. NYU is also planning to have these boards manufactured for the class of 2025 as well.

## Novelty of the Project
Novelty behind the project is the firmware developed for the microcontroller can generate RGB breating effect in a very limited space and resource constrained ATtiny10 microcontroller. This miocontroller features 1 Kilobyte of flash memory and 32 bytes of RAM. While this icrocontroller only supports only 2 PWM pins, I managed to implement a power concious, single-interrupt request process based HSV alorithm that worked as a State-Machine. 

## PCB Art
Monochromatic vector art is imported from any photo editing software like Adobe AI or Inkscape. This is the place where we also set the dimensions of the image we are looking to go with. We want to be sure that the bitmap extracted is of a negative nature or otherwise the dimensions will be altered as the software only extracts the images that touches the bitmap on the extremeties and not the dimensions set by us in the panel.
Once the image is exported as a jpeg, in the KiCad project file  we go to the import bitmap file and calibrate the DPI labels to the values we set while exporitng from the photo editing software. Again we select the negative plot while exporting the procssed image as a KiCad file. This is because we obtained the inverted image in software and we will need to invert this again to obtain the positive mask profile. 

## Circuit 

## Bill Of Materials (BOM)
[Link to the BOM]()

## Firmware
[Code]()

## Some More Images

### Soldermask profile obtained during PCB artwork 

