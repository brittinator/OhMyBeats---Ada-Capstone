// This code is meant to be paired with my fft code in python found at 
// https://github.com/brittinator/OhMyBeats---Ada-Capstone/blob/master/musicFourierTransform.py.
// It's purpose is to control LEDs on the hat. It will be receiving a string of 12 characters long from the computer.
// Brittany L. Walentin October 2015

#include <Adafruit_NeoPixel.h>
#define PIN 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(59, PIN, NEO_GRB + NEO_KHZ800); // I broke 1 LED

// below is an array of each LED's location, in order starting from the beginning to the end
int LED[6][10] = { 
  {100,8,7,6,5,4,3,2,1,0},
  {9,10,11,12,13,14,15,16,17,18},
  {28,27,26,25,24,23,22,21,20,19},
  {29,30,31,32,33,34,35,36,37,38},
  {48,47,46,45,44,43,42,41,40,39},
  {49,50,51,52,53,54,55,56,57,58}
};

//unsigned long time;
int inputArray[6];  // variable that will house the array of numbers
char twoBytes[2];

/// arrays that house the last two iterations of LEDs, for color fading
int minusOne[6]; // n-1 array
int minusTwo[6]; // n-2 array

// colors
// {255,0,0}, // red
// {255,116,0}, //orange
// {255,253,0}, // yellow
// {0,255,0}, // green
// {0,0,255}, // blue
// {134, 2, 171} // purple
 
int PRIMARY[6][3] = {
 {255,0,0}, // red
 {255,116,0}, //orange
 {255,253,0}, // yellow
 {0,255,0}, // green
 {0,0,255}, // blue
 {134, 2, 171} // purple
};

int SECONDARY[6][3] = {
  {0,10,10},
  {0,10,10},
  {0,10,10},
  {0,10,10},
  {0,10,10},
  {0,10,10}
};

int TERNARY[6][3] = {
  {13,0,17},
  {13,0,17},
  {13,0,17},
  {13,0,17},
  {13,0,17},
  {13,0,17}
};

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200); // start serial port at 115200 baud
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
    LedSwitch();  // display pixels!
    if(isOff() == true) {
      turnAllOff;
    }
    strip.show();
  }
} // end of void loop


void LedSwitch() {
  for(int i=0; i < 6; i++) { // bucket index
    for(int n=0; n < 10; n++) { // quantity of LEDs
      if(n < inputArray[i]) {
        strip.setPixelColor(LED[i][n], PRIMARY[i][0], PRIMARY[i][1], PRIMARY[i][2]);        
      } 
      else if(n < minusOne[i]) {
        strip.setPixelColor(LED[i][n], SECONDARY[i][0], SECONDARY[i][1], SECONDARY[i][2]);
      }
      else if(n < minusTwo[i]) {
        strip.setPixelColor(LED[i][n], TERNARY[i][0], TERNARY[i][1], TERNARY[i][2]);
      }
      else {
        strip.setPixelColor(LED[i][n], strip.Color(0,0,0));
      }
    }
  }

  //  set minusTwo array equal to minusOne
  memcpy( minusTwo, minusOne, 12 );
  //  set minusOne array equal to inputArray
  memcpy( minusOne, inputArray, 12 ); // 12 is number of bits to put into array, not array size!!
}  

boolean isOff() {
  for(int i = 0; i < 6; i++) {  
    if(inputArray[i] == 0) {
      return true;
    }
    else { return false; }
  }
}

void turnAllOff() {
  int off[6] = {0,0,0,0,0,0};
  for(int i = 0; i < 60; i++) {
    memcpy(minusOne, off, 6);
    memcpy(minusTwo, off, 6);
    strip.setPixelColor(i, 0);
  }
  strip.setPixelColor(8, 255,255,255);
}

