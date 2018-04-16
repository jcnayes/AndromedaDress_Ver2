// HALLOWEEN 2015: "Andromeda Dress"
//
// Program to control the 16 main 'stars' (NeoPixels) of the Andromeda constellation, 
// sewn onto a black dress.

#include <Adafruit_NeoPixel.h>

// User-defined parameters //////////////////////////////////////////
// LED output pin on Flora
#define PIN_strip1 9   // 1st "line" of stars
#define PIN_strip2 6   // 2nd "line" of stars
#define PIN_strip3 10  // 3rd "line" of stars

// number of NeoPixels to control
#define starCount_strip1 5    // 1st "line" of stars
#define starCount_strip2 8    // 2nd "line" of stars
#define starCount_strip3 3    // 3rd "line" of stars

#define mySpeed 1000  // speed for color changes

// Star color sets
uint32_t cReds[] = {0xFF0000, 0xFF6666, 0x990000, 0x660000, 0xFF3300}; // reds
uint32_t cOrYlBlGr[] = {0xFF9900, 0xFF9933, 0xFF6633, 0xFFFF00, 0x00CC99, 0x00CCCC,0x00FFCC}; // orange, yellow, blue-green
uint32_t cOranges[] = {0xFF6600, 0xFFCC00, 0xFFCC66, 0xCC6600, 0xFF6633}; // oranges
uint32_t cBlueWhite[] = {0xFFFFFF, 0x99FFFF, 0x33FFFF, 0x33CCFF, 0x0000FF, 0x0099FF}; // blue white
uint32_t cWhites[] = {0xFFFFFF, 0xFFCCCC, 0xFFFFCC, 0xCCFFCC, 0xCCFFFF, 0xCCCCFF, 0xFFCCFF}; // whites
uint32_t cYellows[] = {0xFFFF00, 0xFFFF66, 0xFFFFCC, 0xFFCC00}; // yellows
uint32_t cDefault = 0x00FF00; // green default color

// Set up Pixels
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(starCount_strip1, PIN_strip1, NEO_GRB + NEO_KHZ800); // 1st "line" of stars
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(starCount_strip2, PIN_strip2, NEO_GRB + NEO_KHZ800); // 2nd "line" of stars
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(starCount_strip3, PIN_strip3, NEO_GRB + NEO_KHZ800); // 3rd "line" of stars



void setup() {
  strip1.begin();
  strip1.setBrightness(20); // 1/3 brightness to save battery
  strip1.show();            // Initialize all pixels to 'off'
  strip2.begin();
  strip2.setBrightness(20); // 1/3 brightness to save battery
  strip2.show();            // Initialize all pixels to 'off'
  strip3.begin();
  strip3.setBrightness(20); // 1/3 brightness to save battery
  strip3.show();            // Initialize all pixels to 'off'

}

void loop() {
  colorStars(mySpeed);
  
}




// Change the color of each star/pixel, cycling through its color list/array
void colorStars(int wait) {
  
  int arraySize;
  int whichColor;
  uint32_t color;
  
  // Strip 1
  for (int pos = 0; pos < starCount_strip1; pos ++) {
    switch (pos) {    
      // white
      case 0:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cWhites)/4; // divide by 4 b/c size returned in bytes + array values are in bytes
        whichColor = random(arraySize);
        color = cWhites[whichColor]; // get random color from color array      
        strip1.setPixelColor(pos, color);
        break;
      
      // BlueWhite  
      case 1:  // case # is star pos 0, 1, etc
      case 2:
        arraySize = sizeof(cBlueWhite)/4;
        whichColor = random(arraySize);
        color = cBlueWhite[whichColor];
        strip1.setPixelColor(pos, color);
        break;
      
      // yellow  
      case 3:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cYellows)/4;
        whichColor = random(arraySize);
        color = cYellows[whichColor];
        strip1.setPixelColor(pos, color);
        break;
      
      // orange-yellow-blue-green  
      case 4:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cOrYlBlGr)/4;
        whichColor = random(arraySize);
        color = cOrYlBlGr[whichColor];
        strip1.setPixelColor(pos, color);
        break;
        
      default: // be sure to have all position cases called out, or uses a default color
        strip1.setPixelColor(pos, cDefault);
      break;  
    }
  } // end Strip1
 
 
  // Strip 2
  for (int pos = 0; pos < starCount_strip2; pos ++) {
    switch (pos) {  
      // red
      case 0:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cReds)/4; // divide by 4 b/c size returned in bytes + array values are in bytes
        whichColor = random(arraySize);
        color = cReds[whichColor]; // get random color from color array      
        strip2.setPixelColor(pos, color);
        break;
        
      // white
      case 5:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cWhites)/4; // divide by 4 b/c size returned in bytes + array values are in bytes
        whichColor = random(arraySize);
        color = cWhites[whichColor]; // get random color from color array      
        strip2.setPixelColor(pos, color);
        break;
      
      // BlueWhite  
      case 3:  // case # is star pos 0, 1, etc
      case 4:
      case 7:
        arraySize = sizeof(cBlueWhite)/4;
        whichColor = random(arraySize);
        color = cBlueWhite[whichColor];
        strip2.setPixelColor(pos, color);
        break;
      
      // yellow  
      case 6:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cYellows)/4;
        whichColor = random(arraySize);
        color = cYellows[whichColor];
        strip2.setPixelColor(pos, color);
        break;
      
      // orange 
      case 1:  // case # is star pos 0, 1, etc
      case 2:
      arraySize = sizeof(cOranges)/4;
        whichColor = random(arraySize);
        color = cOranges[whichColor];
        strip2.setPixelColor(pos, color);
        break;
        
      default: // be sure to have all position cases called out, or uses a default color
        strip1.setPixelColor(pos, cDefault);
      break;  
    }
  } // end Strip2
 
 
  // Strip 3
  for (int pos = 0; pos < starCount_strip3; pos ++) {
    switch (pos) {    
      // BlueWhite  
      case 0:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cBlueWhite)/4;
        whichColor = random(arraySize);
        color = cBlueWhite[whichColor];
        strip3.setPixelColor(pos, color);
        break;
      
      // orange  
      case 1:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cOranges)/4;
        whichColor = random(arraySize);
        color = cOranges[whichColor];
        strip3.setPixelColor(pos, color);
        break;
      
      // yellow  
      case 2:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cYellows)/4;
        whichColor = random(arraySize);
        color = cYellows[whichColor];
        strip3.setPixelColor(pos, color);
        break;
        
      default: // be sure to have all position cases called out, or uses a default color
        strip3.setPixelColor(pos, cDefault);
      break;  
    }
  } // end Strip3
 
  
  strip1.show();
  strip2.show();
  strip3.show();
  delay(wait);
  
}
