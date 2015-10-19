#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)

// ex data:
// 1s: [5, 10, 3, 1, 0, 0, 0]
// 2s: [5, 10, 3, 1, 0, 0, 0]
// 3s: [7, 10, 3, 2, 1, 0, 0]
// 4s: [5, 10, 3, 1, 0, 0, 0]
// 5s: [6, 10, 3, 1, 0, 0, 0]

// input will be an array with 6 numbers, from subBass on left to treble on right
// loop through the array and light up each bucket with the number of LEDs listed

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  int array[] = {
    1,4,10,2,1,0
  };

//  for(int bucket=0; bucket < 6; bucket++) {
//    if(bucket = 0) {
//      // special case
//      int start = 0;
//    }
//    else {
//    int start = bucket * 10;
//    }
//    int start = 0;
//    for(int i=start; i < start + 10; i++) {
//      for(int j=start; j < start + array[start]; j++) {
//        strip.setPixelColor(j, 50, 70, 0);
//      }
//      // turn off pixels not needed
//      for(int j=start + array[start]; j < start + 10; j++) {
//        strip.setPixelColor(j, 0);
//      }
//  }

  // subBass
  for(int i=0; i < 0 + 10; i++) {
    for(int j=0; j < 0 + array[0]; j++) {
      strip.setPixelColor(j, 50, 70, 0);
    }
    // turn off pixels not needed
    for(int j=0 + array[0]; j < 0 + 10; j++) {
      strip.setPixelColor(j, 0);
    }
  }

   // bass
  for(int i=10; i < 10 + 10; i++) {
    for(int j=10; j < 10 + array[1]; j++) {
      strip.setPixelColor(j, 0, 50, 50);
    }
    // turn off pixels not needed
    for(int j=10 + array[1]; j < 10 + 10; j++) {
      strip.setPixelColor(j, 0);
    }
  }

   // low mid-tones
  for(int i=20; i < 20 + 10; i++) {
    for(int j=20; j < 20 + array[2]; j++) {
      strip.setPixelColor(j, 50, 50, 50);
    }
    // turn off pixels not needed
    for(int j=20 + array[2]; j < 20 + 10; j++) {
      strip.setPixelColor(j, 0);
    }
  }

   // mid-tones
  for(int i=30; i < 30 + 10; i++) {
    for(int j=30; j < 30 + array[2]; j++) {
      strip.setPixelColor(j, 50, 50, 50);
    }
    // turn off pixels not needed
    for(int j=30 + array[3]; j < 30 + 10; j++) {
      strip.setPixelColor(j, 0);
    }
  }

   // high mid-tones
  for(int i=40; i < 40 + 10; i++) {
    for(int j=40; j < 40 + array[4]; j++) {
      strip.setPixelColor(j, 50, 50, 50);
    }
    // turn off pixels not needed
    for(int j=40 + array[4]; j < 40 + 10; j++) {
      strip.setPixelColor(j, 0);
    }
  }

   // treble
  for(int i=50; i < 50 + 10; i++) {
    for(int j=50; j < 50 + array[5]; j++) {
      strip.setPixelColor(j, 0, 0, 100);
    }
    // turn off pixels not needed
    for(int j=50 + array[5]; j < 50 + 10; j++) {
      strip.setPixelColor(j, 0);
    }
  }
strip.show();


}

   
