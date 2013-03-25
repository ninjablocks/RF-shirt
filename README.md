#Wireless Nina's eyes in a T-Shirt

by @justy

OK, there's nothing shirt-specific in the code- you just need 2 RGB LEDs

433 MHz RF receiver plus RGB LEDs

##Full PWM support


##Simple wireless protocol

Each colour component is sent separately.

You send an arm code, then the colour value.

For example, to make purple you would:

1. Send CODE\_ArmR
2. Send CODE\_Base + 255 (40255)
3. Send CODE\_ArmB
4. Send CODE\_Base + 255 (40255)

This code accompanies a how-to found here:
 http://ninjablocks.com/blogs/how-to/7559040-make-a-wearable-ninas-eyes-t-shirt
