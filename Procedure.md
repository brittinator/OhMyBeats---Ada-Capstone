# How To Build a Top Hat Music Equalizer
This is a guide for how to set up and implement a wearable top hat that responds to music input by displaying a visual equalizer.  

"Oh My Beats" as I've called it is a wearable technology that will compliment any person who wants to share their music with people in a novel way.  Oh My Beats aims to be a gender neutral accessory so as to be an inclusive as possible.

This project is a top hat + LEDs that will display a live-view of music playing on a computer.

# Step 1
## Materials & Tools
(All prices in USD)
* Black Top Hat = $12.00
* 1 M x Adafruit NeoPixel Digital RGB LED Strip - Black 60 LED (BLACK) [ID:1461] (http://www.adafruit.com/products/1461) = $24.95
* RedBearLab Blend Micro (http://store.redbearlab.com/products/blendmicro) = $26.90
* 1 x 74AHCT125 - Quad Level-Shifter (3V to 5V) (74AHCT125) [ID:1787] = $1.50
* 1 x 4 x AA Battery Holder with On/Off Switch[ID:830] = $2.95
* 1 x Premium Male/Male Jumper Wires - 20 x 6" (150mm)[ID:1957] = $1.95
* 1 x Female DC Power adapter - 2.1mm jack to screw terminal block[ID:368] =
$2.00
* 1 x Male DC Power adapter - 2.1mm plug to screw terminal block[ID:369] =
$2.00
* resister
* capacitor
* cords  
* solder
* solder gun
* 4 AA rechargeable batteries
* 5V battery holder
* volt meter

NeoPixels are Adafruit's house brand of Red Green Blue (RGB) LEDs (Light Emitting Diodes) that are also addressable.  This means the pixels know their location, which makes programming what you want to display a little easier.

The Blend Micro is an Arduino microcontroller that also houses an on-board bluetooth chip.  The micro utilizes bluetooth 4.0 Low Energy, (BLE) which makes this board not as power hungry as some other arduino shields or raspberry pi dongles. The micro-controller unit (MCU) is Atmel ATmega32U4 and the BLE chip is Nordic nRF8001.

## Software
* Computer: Macbook Pro running Yosemite v 10.10.5
* Processing software: Python 2.7.10 :: Anaconda 2.3.0 (x86_64)
  * Install from [python's website](https://www.python.org/downloads/)
  * You also need to install a python library for serial communication between your computer and the arduino. To do this, in your terminal type `pip install pyserial`
* On-board software: Arduino programming language (based on Wiring), version 1.6.5
  * Install from [Arduino's website](https://www.arduino.cc/en/Guide/HomePage)
* Follow getting started [manual](http://redbearlab.com/getting-started-blendmicro) on how to get the libraries for the Blend Micro. I followed the [Quickstart with Codebender](http://redbearlab.com/quick-start-codebender) link.  
* Follow this link for how to install the Neopixel Arduino Library [here](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library)

# Step 2
## Safety !!

* Polarized capacitors can heat up/burst if installed in the wrong direction. Place the negative side with the ground wire.

* Disconnect all power sources before modifying a circuit.

* You will be putting electricity close to your body and skin, which can cause burns.  Please be careful and cover any exposed wires before trying anything on.

From Adafruit's Neopixel [Uberguide](https://learn.adafruit.com/adafruit-neopixel-uberguide/overview)


> * Before connecting NeoPixels to any power source, add a large capacitor (1000 µF, 6.3V or higher) across the + and – terminals as shown above.
* Place a 300 to 500 Ohm resistor between the Arduino data output pin and the input to the first NeoPixel. This resistor must be at the NeoPixel end of the wire to be effective! Some products already incorporate this resistor…if you’re not sure, add one…there’s no harm in doubling up!
* Try to minimize the distance between the Arduino and first pixel.
* Avoid connecting NeoPixels to a live circuit. If you simply must, always connect ground first, then +5V, then data. Disconnect in the reverse order.
* If powering the pixels with a separate supply, apply power to the pixels before applying power to the microcontroller.
* Observe the same precautions as you would for any static-sensitive part; ground yourself before handling, etc.
* NeoPixels powered by 5v require a 5V data signal. If using a 3.3V microcontroller you must use a logic level shifter such as a 74AHCT125 or 74HCT245. (If you are powering your NeoPixels with 3.7v like from a LiPoly, a 3.3v data signal is OK)
* Make sure that your connections are secure. Alligator clips do not make reliable connections to the tiny solder pads on NeoPixel rings. Better to solder a small pigtail wire to the ring and attach the alligator clips to that.




## Hint
To troubleshoot my python code, I used _Jupyter_, which is a web application that allows you to modify live code, look at visualizations and and see the errors live.
To start python notebooks, open up terminal and type `$ipython notebook`.



`ls /dev/tty.*` in terminal to see what your ports are, then

`screen` and the name of the port, then what your baud rate it, ex: mine was: `screen /dev/tty.usbmodem1411 9600`
