#include <Adafruit_NeoPixel.h>
// programming language: wiring, variant on processing

#define PIN 8
// To Do: !! figure out timing for data packets for a delay
unsigned long time;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // void means you will not have a return for this method
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // start serial port at 115200 baud:
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

//  establishContact();  // send a byte to establish contact until receiver responds
} // end of setup

int inputArray[6];  // variable that will house the array of numbers
char twoBytes[2];

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
//    delay(100);
  }

} // end of void loop

void LedSwitch() {
  // subBass
      for(int i=0; i < 0 + 10; i++) { // from 0-9 pixel locale
        for(int j=0; j < 0 + inputArray[0]; j++) {
          strip.setPixelColor(j, 90, 190, 90);
        }
        // turn off pixels not needed
        for(int j=0 + inputArray[0]; j < 0 + 10; j++) {
          strip.setPixelColor(j, 0);
        }
      } // end of first section

       // bass
      for(int i=10; i < 10 + 10; i++) {
        for(int j=10; j < 10 + inputArray[1]; j++) {
          strip.setPixelColor(j, 255, 255, 255);
        }
        // turn off pixels not needed
        for(int j=10 + inputArray[1]; j < 10 + 10; j++) {
          strip.setPixelColor(j, 0);
        }
      } // end of second section

       // low mid-tones
      for(int i=20; i < 20 + 10; i++) {
        for(int j=20; j < 20 + inputArray[2]; j++) {
          strip.setPixelColor(j, 255, 255, 0);
        }
        // turn off pixels not needed
        for(int j=20 + inputArray[2]; j < 20 + 10; j++) {
          strip.setPixelColor(j, 0);
        }
      }  // end of third section

       // mid-tones
      for(int i=30; i < 30 + 10; i++) {
        for(int j=30; j < 30 + inputArray[3]; j++) {
          strip.setPixelColor(j, 255, 150, 0);
        }
        // turn off pixels not needed
        for(int j=30 + inputArray[3]; j < 30 + 10; j++) {
          strip.setPixelColor(j, 0);
        }
      }  // end of fourth section

       // high mid-tones
      for(int i=40; i < 40 + 10; i++) {
        for(int j=40; j < 40 + inputArray[4]; j++) {
          strip.setPixelColor(j, 0, 80, 100);
        }
        // turn off pixels not needed
        for(int j=40 + inputArray[4]; j < 40 + 10; j++) {
          strip.setPixelColor(j, 0);
        }
      } // end of fifth section

       // treble
      for(int i=50; i < 50 + 10; i++) {
        for(int j=50; j < 50 + inputArray[5]; j++) {
          strip.setPixelColor(j, 100, 0, 100);
        }
        // turn off pixels not needed
        for(int j=50 + inputArray[5]; j < 50 + 10; j++) {
          strip.setPixelColor(j, 0);
        }
      } // end of sixth section
}
