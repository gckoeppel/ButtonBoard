# ButtonBoard

Most kids

 - love buttons
 - love toys that make sound
 - love LEDs

This project combines these features in one box. This allows us to test if our kid is part of "most kids".

## Hardware
The main hardware parts are:

 - Adafruit Feather 32u4 Basic Proto
 - ADS1015 Breakout Board (4 analog inputs)
 - Adafrui GPIO Expander Bonnet (16 digital I/O)
 - Music Maker FeatherWing
 - PowerBoost 500 Basic 5V to create a 5V supply for the LED in the buttons. Some of them can't run at 3.3V
 - Stereo Speakers
 - USB Type-C Connector for charging, programming and debugging 
 - A bag full of buttons, switches, sliders, potentiometers and LEDs
 - A wooden box
 - Lots of wires and solder

## Software

IDE used for coding is PlatformIO.
Software is written in C++, using the following libraries:

 - Adafruit ADS1X15
 - Adafruit MCP23017 Arduino Library
 - Thread
 