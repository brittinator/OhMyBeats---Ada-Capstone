// This code is meant to be paired with my fft code in python found at 
// https://github.com/brittinator/OhMyBeats---Ada-Capstone/blob/master/musicFourierTransform.py.
// It's purpose is to control LEDs on the hat. It will be receiving a string of 12 characters long from the computer.
// Brittany L. Walentin October 2015
#include <Adafruit_NeoPixel.h>

#define PIN 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(59, PIN, NEO_GRB + NEO_KHZ800); // 1 LED was given as tribute to the soldering gods

unsigned long time;
int inputArray[6];  // variable that will house the array of numbers
char twoBytes[2];
int incrementor = 0;
const int high = 100;
const int med = 50;
const int low = 20;

void setup() {
  // void means you will not have a return for this method
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // start serial port at 115200 baud:
  Serial.begin(115200);
}

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
  // subBass
  for(int i=8; i > -1; i--) { // from 0-8 pixel locale
    for(int j=8; j > 8-inputArray[0]; j--) {
      strip.setPixelColor(j, incrementor, 0, low);
    }
    // turn off pixels not needed
    for(int j=8 - inputArray[0]; j > -1; j--) {
      strip.setPixelColor(j, 0);
    }
  } // end of first section

   // bass
  for(int i=9; i < 19; i++) {
    for(int j=9; j < 9 + inputArray[1]; j++) {
      strip.setPixelColor(j, incrementor, high, 0);
    }
    // turn off pixels not needed
    for(int j=9 + inputArray[1]; j < 19; j++) {
      strip.setPixelColor(j, 0);
    }
  } // end of second section

   // low mid-tones
  for(int i=28; i > 18; i--) {
    for(int j=28; j > 28 - inputArray[2]; j--) {
      strip.setPixelColor(j, 0, incrementor, med);
    }
    // turn off pixels not needed
    for(int j=28 - inputArray[2]; j > 18; j--) {
      strip.setPixelColor(j, 0);
    }
  }  // end of third section

   // mid-tones, green
  for(int i=29; i < 39; i++) {
    for(int j=29; j < 29 + inputArray[3]; j++) {
      strip.setPixelColor(j, med, incrementor, 0);
    }
    // turn off pixels not needed
    for(int j=29 + inputArray[3]; j < 39; j++) {
      strip.setPixelColor(j, 0);
    }
  }  // end of fourth section

   // high mid-tones
  for(int i=48; i > 38; i--) {
    for(int j=48; j > 48 - inputArray[4]; j--) {
      strip.setPixelColor(j, 0, med, incrementor);
    }
    // turn off pixels not needed
    for(int j=48-inputArray[4]; j > 38; j--) {
      strip.setPixelColor(j, 0);
    }
  } // end of fifth section

   // treble
  for(int i=49; i < 59; i++) {
    for(int j=49; j < 50 + inputArray[5]; j++) {
      strip.setPixelColor(j, 0, high, incrementor);
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
