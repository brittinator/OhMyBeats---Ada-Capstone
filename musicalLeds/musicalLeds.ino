// This code is meant to be paired with my fft code in python found at 
// https://github.com/brittinator/OhMyBeats---Ada-Capstone/blob/master/musicFourierTransform.py.
// This code's purpose is to control LEDs on the hat. It will be receiving a string of 12 characters long from the computer.
// Brittany L. Walentin October 2015

#include <Adafruit_NeoPixel.h>
#define PIN 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(59, PIN, NEO_GRB + NEO_KHZ800); // I broke 1 LED

// below is an array of each LED's location, in order starting from beginning to the end
int LED[6][10] = { 
  {1000,8,7,6,5,4,3,2,1,0}, // 1000 is a placeholder for the LED I broke; does nothing
  {9,10,11,12,13,14,15,16,17,18},
  {28,27,26,25,24,23,22,21,20,19},
  {29,30,31,32,33,34,35,36,37,38},
  {48,47,46,45,44,43,42,41,40,39},
  {49,50,51,52,53,54,55,56,57,58}
};

int inputArray[6];  // variable that will house the array of numbers
/// arrays that house the last two iterations of LEDs, for color fading //////////
int minusOne[6]; // n-1 array
int minusTwo[6]; // n-2 array
char twoBytes[2]; // temporary slot for 2 characters at a time, i.e. "0" + "7"

////////////////////  colors   //////////////////////////////////////////////////
// {255,0,0}, // red
// {255,116,0}, //orange
// {255,253,0}, // yellow
// {0,255,0}, // green
// {0,0,255}, // blue
// {134, 2, 171} // purple
 
int PRIMARY[6][3] = {
 {255,0,0}, // red
 {205,116,0}, //orange
 {155,153,0}, // yellow
 {0,255,0}, // green
 {0,0,255}, // blue
 {134, 2, 171} // purple
};

int SECONDARY[6][3] = {
  {0,10,10}, // light blue
  {0,10,10},
  {0,10,10},
  {0,10,10},
  {0,10,10},
  {0,10,10}
};

int TERNARY[6][3] = {
  {13,0,17}, // purple
  {13,0,17},
  {13,0,17},
  {13,0,17},
  {13,0,17},
  {13,0,17}
};
////////////////////////////////////////////////////////////////////////

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200); // serial port set to 115200 baud
}

void loop() {
  bool wrote = false;

  // if we get a valid byte, read it
  while (Serial.available() > 0) {
    // get incoming byte
    for (int i = 0; i < 6; i++) {
      Serial.readBytes(twoBytes, 2); // buffer is twoBytes, of length 2
      // re-casting character array into a 1. string, then 2. integer
      inputArray[i] = String(twoBytes).toInt(); 
    }

    wrote = true;
  } // end of while

  if (wrote) {
    LedSwitch();
//    if(isOff()) {
//      turnAllOff();
//    }
    strip.show();
  }
} // end of void loop

void LedSwitch() {
  // turns LEDs on/off based on inputArray, minusOne array and minusTwo array
  for(int i=0; i < 6; i++) { // frequency buckets
    for(int n=0; n < 10; n++) { // quantity of LEDs in each bucket
      if(n < inputArray[i]) {
        // if the number of LED it's on is inside the input array, turn on the LED at this location
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

  //  set minusTwo array equal to minusOne's contents
  memcpy( minusTwo, minusOne, 12 );
  //  set minusOne array equal to inputArray's contents
  memcpy( minusOne, inputArray, 12 ); // 12 is number of bits to put into array, not array size!!
}  

boolean isOff() {
  // checks to see if inputArray contains all zeros, a signature that song is finished
  boolean isOff = true;
  for(int i = 0; i < 6; i++) {  
    if(!inputArray[i] == 0) {
      isOff = false;
    }
  }
  return isOff;
}

void turnAllOff() {
  for(int i = 0; i < 60; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
}

