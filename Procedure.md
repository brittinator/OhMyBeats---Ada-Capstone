# Procedure
This is a guide for how to set up and implement a wearable top hat that responds to music input by displaying a visual equalizer.

## Materials
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

NeoPixels are Adafruit's house brand of Red Green Blue (RGB) LEDs (Light Emitting Diodes) that are also addressable.  This means the pixels know their location, which makes programming what you want to display a little easier.

The Blend Micro is an Arduino microcontroller that also houses an on-board bluetooth chip.  The micro utilizes bluetooth 4.0 Low Energy, (BLE) which makes this board not as power hungry as some other arduino shields or raspberry pi dongles. The micro-controller unit (MCU) is Atmel ATmega32U4 and the BLE chip is Nordic nRF8001.

## Software
* Computer: Macbook Pro running Yosemite v 10.10.5
* Processing software: Python 2.7.10 :: Anaconda 2.3.0 (x86_64)
  * Install from [python's website](https://www.python.org/downloads/)
* On-board software: In-house C++ using Arduino IDE, version 1.6.5
  * Install from [Arduino's website](https://www.arduino.cc/en/Guide/HomePage)
* Follow getting started [manual](http://redbearlab.com/getting-started-blendmicro) on how to get the extra libraries needed. I followed the [Quickstart with Codebender](http://redbearlab.com/quick-start-codebender) link.  

*


to start python notebooks: `$ipython notebook`


libsndfile
`brew install libsndfile`

to install FFTW v 3.3.4 C library
```
cd into the folder
$ cd ~/Downloads/fftw-3.3.4
$ gem install ruby-fftw3
$ less INSTALL
$ ./configure
$ make
$ make install
```

in Gemfile:
```
source 'https://rubygems.org'

gem 'fftw3'
gem 'ruby-audio', '~> 1.6.1'
gem 'narray', '~> 0.6.1.1'
```
in terminal
`install bundler`
`bundle`
