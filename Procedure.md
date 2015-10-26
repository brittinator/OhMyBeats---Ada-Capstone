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
* screw driver
* CATT5 cable to cannibalize cords
* electrical tape/heat shrink for covering exposed wires

NeoPixels are Adafruit's house brand of Red Green Blue (RGB) LEDs (Light Emitting Diodes) that are also addressable.  This means the pixels know their location, which makes programming what you want to display a little easier.

The Blend Micro is an Arduino microcontroller that also houses an on-board bluetooth chip.  The micro utilizes bluetooth 4.0 Low Energy, (BLE) which makes this board not as power hungry as some other arduino shields or raspberry pi dongles. The micro-controller unit (MCU) is Atmel ATmega32U4 and the BLE chip is Nordic nRF8001.

## Software
* Computer: Macbook Pro running Yosemite v 10.10.5
* Processing software: Python 2.7.10 :: Anaconda 2.3.0 (x86_64)
  * Install from [python's website](https://www.python.org/downloads/)
  * You also need to install a python library for serial communication between your computer and the arduino. To do this, in your terminal type `pip install pyserial`
* On-board software: Arduino programming language (based on C/C++), version 1.6.5
  * Install from [Arduino's website](https://www.arduino.cc/en/Guide/HomePage)
* Follow getting started [manual](http://redbearlab.com/getting-started-blendmicro) on how to get the libraries for the Blend Micro. I followed the [Quickstart with Codebender](http://redbearlab.com/quick-start-codebender) link.  
* Follow this link for how to install the Neopixel Arduino Library [here](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library)

# Step 2
## Safety <img src="https://raw.githubusercontent.com/brittinator/OhMyBeats---Ada-Capstone/master/Images/caution.png" width=100px>

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


# Step 3
## Prototype Schematic
* I attached my components with a breadboard (no soldering necessary) as a first step.

*  Run the 'strandtest' that comes with the Neopixel library to make sure the Aruino is communicating with your neopixels. Open the Arduino program, and navigate to:
`file -> examples -> Adafruit Neopixels -> strandtest`


![schematic](https://raw.githubusercontent.com/brittinator/OhMyBeats---Ada-Capstone/master/Images/Schematic-OhMyBeats.png)

# Step 4
## Python Code

My python code is in my GitHub repo [here](https://github.com/brittinator/OhMyBeats---Ada-Capstone/blob/master/musicFourierTransform.py).

The code below is doing all the heavy lifting of playing the music, and manipulating it into frequency numbers. It takes a wave file, performs a fast fourier transform, averages the results, and then normalizes the data to fit the number of LEDs the hat has.

The last steps this code does is send a string of 12 numbers to the Arduino, then sends a signal to turn off the LEDs.

```python
"""
This file is meant to feed an Arduino Blend Micro with data.
A fast fourier transform is performed on an imcoming music file,
and then subsequentely averaged and normalized to the number of LEDs attached to the Arduino.
I have 60 (-1, I broke one pixel) neopixels attached and have 6 buckets, so 10 LEDs/bucket.
I normalize my data from 0-10.
"""
# Dependencies/libraries to import
from scipy import fft, arange
from scipy.io import wavfile # for chunking sounds into time slices
import pyaudio # to play audio
import wave # for opening wavefiles
import serial # for serial communication
import time # for timing things/time delays on python side
# -------------------------------------------------
def returnSpectrum(y,Fs):
    """
    Plots a Single-Sided Amplitude Spectrum of y(t)
    y = wavefile in array form
    Fs = sample frequency, sometimes called sampling rate; likely 44100
    """

    n = len(y) # length of the signal
    k = arange(n) # array from [0, 1, 2, ... n-1]
    T = n/float(Fs) # need to make Fs a float so T can be 0.xx decimal

    if y.ndim > 1: # stereo music has more than one dimension for stereo sound
        y = y[:,0] # taking 1st dimension, slice of matrix

    frq = k/T # two sides frequency range
    # take array, divide by num secs
    frq = frq[range(n/2)] # one side frequency range

    Y = fft(y)/n # fft computing and normalization
    Y = Y[range(n/2)]

    zipped =  zip(frq, abs(Y)) # takes 2 arrays of same size & combines

    frequencies = dict(zipped)
    return frequencies

# -------------------------------------------------
def averaging(min, max, spectrum):
    """normalizing a bucket, returns a number from 0-1"""
    length = 0
    sum = 0

    for key in spectrum:
        if key > min and key <= max:
            length += 1
            sum += spectrum[key]

    average = sum/length
    return average

# -------------------------------------------------
def formatData(array):
    """takes an array and adds a leading zero
    then joins all into a string of length 12
    so we'll consistentely send a chunk of data of length 12 to the Arduino"""

    stringArray = []
    for n in array:
        # convert number into a string
        numAsString = str(n)
        if len(numAsString) < 2:
            # add leading zeros to numbers
            numAsString = '0' + numAsString
        stringArray.append(numAsString)

    # join array items into a string of length 12
    return ''.join(stringArray)

# -------------------------------------------------
def buckets(spectrumHash):
    """Mundges data from a huge list of frequency data into 6 distinct buckets"""
    equalizer = []
    normalized = []

    LEDS = 10 # number of leds in each 'frequency bucket'
    SUBBASS =       [20, 60]            # Sub Bass: 20 to 60 Hz
    BASS1 =         [60, 150]           # Bass1: 60 to 150 Hz
    BASS2 =         [150, 250]          # Bass2: 150 to 250 Hz
    LOWMIDRANGE =   [250, 375]          # Low Midrange: 250 to 375 Hz
    MIDRANGE =      [375, 500]           # Midrange: 275 to 500 Hz
    TREBLE =        [500, 2000]        # Treble: 500 Hz to 2 kHz

    subBass =       averaging(SUBBASS[0], SUBBASS[1], spectrumHash)
    bass1 =         averaging(BASS1[0], BASS1[1], spectrumHash)
    bass2 =         averaging(BASS2[0], BASS2[1], spectrumHash)
    lowMidrange =   averaging(LOWMIDRANGE[0], LOWMIDRANGE[1], spectrumHash)
    midrange =      averaging(MIDRANGE[0], MIDRANGE[1], spectrumHash)
    treble =        averaging(TREBLE[0], TREBLE[1], spectrumHash)

    # normalizing buckets - 0 is no leds lit, 10 is all 10 leds in a strip lit
    beforeNormalization = [subBass, bass1, bass2, lowMidrange, midrange, treble]
    hi = max(beforeNormalization)
    lo = min(beforeNormalization)

    for n in beforeNormalization:
        norms = int((((n-lo)/(hi-lo)))*LEDS)
        normalized.append(norms)
    return normalized

# -------------------------------------------------
# test files to play
baseFolder = './AudioFiles/'
sweep = baseFolder +'sweep20-20k.wav'
hz60 = baseFolder +'60hz.wav'
hz200 = baseFolder +'200hz.wav'
hz1000 = baseFolder +'1000hz.wav'
hz3000 = baseFolder +'3000hz.wav'
drum = baseFolder +'drum.wav'
# -------------------------------------------------
""" Below is where the code executes the fft
and send the arrays of LEDs to light to the Arduino"""

sampFreq, snd = wavfile.read(light30)

second = sampFreq # sampling frequency is = second of data
window_size = second/40 # want 40 frames per second (fps), so want 40 windows/second

connection = '/dev/cu.usbmodem1411'

ser = serial.Serial(connection, 115200, timeout=1)

#open a wav format music
f = wave.open(light30,"rb") #rb - read binary

#instantiate PyAudio
p = pyaudio.PyAudio()

# define callback
def callback(in_data, frame_count, time_info, status):
    data = f.readframes(frame_count)
    return (data, pyaudio.paContinue)

#open stream
stream = p.open(format = p.get_format_from_width(f.getsampwidth()),
                channels = f.getnchannels(),
                rate = f.getframerate(),
                output = True,
                stream_callback=callback)

stream.start_stream()

numSlices = 0
for i in range(0, len(snd)-window_size, (window_size)): # range makes an array auto
    numSlices += 1
    spectrum = returnSpectrum(snd[i:i+window_size], sampFreq)
    array = buckets(spectrum)
    data = formatData(array)
    ser.write(data)
    time.sleep(0.020) # delay of 1/40fps = 0.020

# print numSlices
# wait for stream to finish (5)
while stream.is_active():
    time.sleep(0.1)

ser.write("000000000000") # turn LEDs off
#stop stream
stream.stop_stream()
stream.close()
f.close()

#close PyAudio
p.terminate()

```

# Step 5
## Arduino Code
My Arduino code is also on Github [here](https://github.com/brittinator/OhMyBeats---Ada-Capstone/blob/master/musicalLeds/musicalLeds.ino).

This code is written in Arduino's language and (I've been told) is similar to Java and C++. The whole Arduino interface is built upon loops, so you'll see a bunch of those in the following code.  It's purpose is to control the LEDs on the hat. It will be receiving a string of 12 characters long from the computer.

```
#include <Adafruit_NeoPixel.h>
// programming language: wiring, variant on processing

#define PIN 8 // the pin the LED string is attached to.
unsigned long time;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(59, PIN, NEO_GRB + NEO_KHZ800);
// 1 LED was given as tribute to the soldering gods
int BUCKET = 10; // size of each equalizer bar, currently not used
int inputArray[6];  // variable that will house the array of numbers
char twoBytes[2];
int incrementor = 0;

void setup() {
  // void means you will not have a return for this method
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // start serial port at 115200 baud:
  Serial.begin(115200);
} // end of setup

void loop() {
  bool wrote = false;

  // if we get a valid byte, read analog int:
  while (Serial.available() > 0) {
    // get incoming byte
    for (int i = 0; i < 6; i++) {
      Serial.readBytes(twoBytes, 2); // buffer is twoBytes, of length 2
      inputArray[i] = String(twoBytes).toInt(); // re-casting character array into a 1. string, then 2. integer
    }

    wrote = true;
  } // end of while

  if (wrote) {
    // display pixels!
    LedSwitch();
    strip.show();
  }
} // end of void loop

void LedSwitch() {
  // subBass red
  for(int i=8; i > -1; i--) { // from 0-8 pixel locale
    for(int j=8; j > 8-inputArray[0]; j--) {
      strip.setPixelColor(j, 255, 0, incrementor);
    }
    // turn off pixels not needed
    for(int j=8 - inputArray[0]; j > -1; j--) {
      strip.setPixelColor(j, 0);
    }
  } // end of first section

   // bass orange
  for(int i=9; i < 19; i++) {
    for(int j=9; j < 9 + inputArray[1]; j++) {
      strip.setPixelColor(j, 200, incrementor, 0);
    }
    // turn off pixels not needed
    for(int j=9 + inputArray[1]; j < 19; j++) {
      strip.setPixelColor(j, 0);
    }
  } // end of second section

   // low mid-tones, upside down, yellow
  for(int i=28; i > 18; i--) {
    for(int j=28; j > 28 - inputArray[2]; j--) {
      strip.setPixelColor(j, 255, incrementor, 0);
    }
    // turn off pixels not needed
    for(int j=28 - inputArray[2]; j > 18; j--) {
      strip.setPixelColor(j, 0);
    }
  }  // end of third section

   // mid-tones, green
  for(int i=29; i < 39; i++) {
    for(int j=29; j < 29 + inputArray[3]; j++) {
      strip.setPixelColor(j, incrementor, 255, 0);
    }
    // turn off pixels not needed
    for(int j=29 + inputArray[3]; j < 39; j++) {
      strip.setPixelColor(j, 0);
    }
  }  // end of fourth section

   // high mid-tones, blue
  for(int i=48; i > 38; i--) {
    for(int j=48; j > 48 - inputArray[4]; j--) {
      strip.setPixelColor(j, incrementor, 0, 255);
    }
    // turn off pixels not needed
    for(int j=48-inputArray[4]; j > 38; j--) {
      strip.setPixelColor(j, 0);
    }
  } // end of fifth section

   // treble, violet
  for(int i=49; i < 59; i++) {
    for(int j=49; j < 50 + inputArray[5]; j++) {
      strip.setPixelColor(j, incrementor, 0, 255);
    }
    // turn off pixels not needed
    for(int j=49 + inputArray[5]; j < 59; j++) {
      strip.setPixelColor(j, 0);
    }
  } // end of sixth section
  if(incrementor == 200) {
    incrementor == -1;
  }
  incrementor += 1;
}

```
* At this point I would load in a few test sound files with known frequencies. You should be able to see a certain bucket light up for that freqency. For example, if you run the 60-hz.wav file, you should ony see the first 10 LEDs light up for the duration of the sound file because this bucket encompasses frequencies from 20-60 Hertz.

* If all went well, continue onto step 5. Otherwise, look back at the code, and check your breadboard connections.

# Step 5
## Hat Construction

* Before this step, I would make sure both programs above are behaving properly.  It is easier to debug the whole thing in prototype stage rather than trying to determine if the problem is wiring vs. code not functioning.

* Test our your soldering techniques on some wire or components you won't need before jumping into soldering the crucial parts.

* I've used green wire for the data, red/orange wire for power, and black for the ground.

* Turn off/unplug your power sources while soldering.

* Cut the Neopixels in the middle of the three copper oblongs.  These are what you'll be soldering to.  I cut too much on one side on the first cut, so I had toss that LED and adjust my code for 59 pixels instead of 60.

This is where you'll solder your pieces together.  If you have a volt meter, now is the time to use it.  

I soldered bits at a time, and when I got the battery pack soldered to the arduino and the first set of LEDs, I downloaded the strandtest that comes with the neopixel example library, and powered on the LEDs. You should see them light up, and if not check your connections before moving on. Also feel free to use your volt meter.

I repeated this process with each new LED strand I connected.

I drilled holes on the top and bottom of the front panel of the hat. This is where the wires will thread through, and also helps secure the LEDs. When you are finished, use shrink wrap or electrical tape to protect yourself from any exposed wires. This will also help decrease oxidation of the wires, which will make your project last longer.
