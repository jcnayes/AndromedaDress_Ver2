// HALLOWEEN 2015: "Andromeda Dress"
//
// Program to control the 16 main 'stars' (NeoPixels) of the Andromeda constellation, 
// sewn onto a black dress.
//
// 2016-08: Added LSM303DLHC accelerometer functionality
// 2018-04: New twinkle settings


#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

// User-defined parameters //////////////////////////////////////////
// LED output pin on Flora
#define PIN_strip1 9   // 1st "line" of stars
#define PIN_strip2 6   // 2nd "line" of stars
#define PIN_strip3 10  // 3rd "line" of stars

// number of NeoPixels to control- Changing the amount of stars in each line? Update the cases in colorStars()
#define starCount_strip1 5    // 1st "line" of stars
#define starCount_strip2 8    // 2nd "line" of stars
#define starCount_strip3 3    // 3rd "line" of stars

#define mySpeed 10  // speed for color changes

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

//Set up accelerometer, assign a unique ID to this sensor at the same time
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(1337);
double vector1, vector2;
sensors_event_t event, event2;

// Change this number to adjust TWINklitude :)
// lower number = more sensitive
#define MOVE_THRESHOLD 1

void setup() {
  
  Serial.begin(9600);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!accel.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }

  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip1.setBrightness(20);  // 1/3 brightness to save battery
  strip2.setBrightness(20);
  strip3.setBrightness(20);
  lightsOut();               // Initialize all pixels to 'off'

}


void loop() {
  // Normally, the stars will twinkle according to the set star colors.
  // If motion is detected, the stars will twinkle at a higher brightness.
  
  /* Get a new sensor event */ 
  sensors_event_t event;
  accel.getEvent(&event);
  vector1 = getVectorMagnitude(event);
  Serial.print("Length: "); Serial.println(vector1);
  
  // wait a bit
  delay(50);
  
  // get new data!
  accel.getEvent(&event);
  vector2 = getVectorMagnitude(event);
  Serial.print("New Length: "); Serial.println(vector2);

  // are we moving?
  if (abs(vector2 - vector1) > MOVE_THRESHOLD) {
    
    Serial.print("Twinkle! (Vector diff = ") + Serial.println(abs(vector2 - vector1));
    strip1.setBrightness(40);
    strip2.setBrightness(40);
    strip3.setBrightness(40);
    
    int tempTwink = 0;
    while(tempTwink < 10) {
      
      Twinkle();
      delay(100);
      tempTwink++;
    }
    
    strip1.setBrightness(20);
    strip2.setBrightness(20);
    strip3.setBrightness(20);
    Serial.println("Twinkle done");
    
  } else {
    
//    colorAllStars(); // standard star colors, no/low motion detected
    
    colorSomeStars(random(4)); // standard star colors, no/low motion detected, only update a few stars at a time
    
//   flashRandom(1);
//   delay(mySpeed); 
//   flashRandom(3);
//   delay(mySpeed); 
//   flashRandom(2);
//   delay(mySpeed); 
//   flashRandom(4);
//   delay(mySpeed); 
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////


// Get the magnitude (length) of the 3 axis vector
//   http://en.wikipedia.org/wiki/Euclidean_vector#Length
double getVectorMagnitude(sensors_event_t event) {
  
  double newVector = event.acceleration.x*event.acceleration.x;
  newVector += event.acceleration.y*event.acceleration.y;
  newVector += event.acceleration.z*event.acceleration.z;
  newVector = sqrt(newVector);
  
  return newVector;
}


// Change the color of each star/pixel, science colors
void colorAllStars() {
  
  int arraySize_max = max((starCount_strip1,starCount_strip2),starCount_strip3);
  
  for (int pos = 0; pos < arraySize_max; pos ++) {
    setScienceColor(pos, pos, pos);
  }
  
  strip1.show();
  strip2.show();
  strip3.show();
}


// Change the color of up to (howmany) number of stars/pixels, science colors
// Same number of pixels lit up on each star string
void colorSomeStars(uint8_t howmany) {
  
  for(uint16_t i=0; i<howmany; i++) {
    
    // get a random pixel from the list
    int j_1 = random(strip1.numPixels());
    int j_2 = random(strip2.numPixels());
    int j_3 = random(strip3.numPixels());

    setScienceColor(j_1, j_2, j_3);
  }
  
  strip1.show();
  strip2.show();
  strip3.show();
}


// Change the color of a specific star/pixel, randomly picked from its color array
// (Max out position to make no changes to a string).
// Does not light up pixels.
void setScienceColor(int posS1, int posS2, int posS3) {
  
  int arraySize;
  int whichColor;
  uint32_t color;
  
  // Strip 1: 5 pixels
    switch (posS1) {    
      // white
      case 0:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cWhites)/4; // divide by 4 b/c size returned in bytes + array values are in bytes
        whichColor = random(arraySize);
        color = cWhites[whichColor]; // get random color from color array
        break;
      
      // BlueWhite  
      case 1:  // case # is star pos 0, 1, etc
      case 2:
        arraySize = sizeof(cBlueWhite)/4;
        whichColor = random(arraySize);
        color = cBlueWhite[whichColor];
        break;
      
      // yellow  
      case 3:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cYellows)/4;
        whichColor = random(arraySize);
        color = cYellows[whichColor];
        break;
      
      // orange-yellow-blue-green  
      case 4:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cOrYlBlGr)/4;
        whichColor = random(arraySize);
        color = cOrYlBlGr[whichColor];
        break;
        
      default: // be sure to have all position cases called out, or uses a default color
        color = cDefault;
      break;  
    } 
    strip1.setPixelColor(posS1, color);
    // end Strip1
 
 
  // Strip 2: 8 pixels
    switch (posS2) {  
      // red
      case 0:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cReds)/4;
        whichColor = random(arraySize);
        color = cReds[whichColor];
        break;
        
      // white
      case 5:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cWhites)/4;
        whichColor = random(arraySize);
        color = cWhites[whichColor];
        break;
      
      // BlueWhite  
      case 3:  // case # is star pos 0, 1, etc
      case 4:
      case 7:
        arraySize = sizeof(cBlueWhite)/4;
        whichColor = random(arraySize);
        color = cBlueWhite[whichColor];
        break;
      
      // yellow  
      case 6:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cYellows)/4;
        whichColor = random(arraySize);
        color = cYellows[whichColor];
        break;
      
      // orange 
      case 1:  // case # is star pos 0, 1, etc
      case 2:
      arraySize = sizeof(cOranges)/4;
        whichColor = random(arraySize);
        color = cOranges[whichColor];
        break;
        
      default: // be sure to have all position cases called out, or uses a default color
        color = cDefault;
      break;  
    }
    strip2.setPixelColor(posS2, color);
  // end Strip2
 
 
  // Strip 3: 3 pixels
    switch (posS3) {    
      // BlueWhite  
      case 0:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cBlueWhite)/4;
        whichColor = random(arraySize);
        color = cBlueWhite[whichColor];
        break;
      
      // orange  
      case 1:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cOranges)/4;
        whichColor = random(arraySize);
        color = cOranges[whichColor];
        break;
      
      // yellow  
      case 2:  // case # is star pos 0, 1, etc
        arraySize = sizeof(cYellows)/4;
        whichColor = random(arraySize);
        color = cYellows[whichColor];
        break;
        
      default: // be sure to have all position cases called out, or uses a default color
        color = cDefault;
      break;  
    }
    strip3.setPixelColor(posS3, color);
    // end Strip3
}


// 'Twinkle' each star/pixel, by random selection from the cWhites color array
void Twinkle() {
  
  int arraySize;
  int whichColor;
  uint32_t color;
  
  // Strip 1: 5 pixels
  for (int pos = 0; pos < starCount_strip1; pos ++) {
    
    // all stars in whites
    arraySize = sizeof(cWhites)/4; // divide by 4 b/c size returned in bytes + array values are in bytes
    whichColor = random(arraySize);
    color = cWhites[whichColor]; // get random color from color array      
    strip1.setPixelColor(pos, color);
  }
 
  // Strip 2: 8 pixels
  for (int pos = 0; pos < starCount_strip2; pos ++) {
    
    // all stars in whites
    arraySize = sizeof(cWhites)/4; // divide by 4 b/c size returned in bytes + array values are in bytes
    whichColor = random(arraySize);
    color = cWhites[whichColor]; // get random color from color array      
    strip2.setPixelColor(pos, color);
  }
 
  // Strip 3: 3 pixels
  for (int pos = 0; pos < starCount_strip3; pos ++) {
    
    // all stars in whites
    arraySize = sizeof(cWhites)/4; // divide by 4 b/c size returned in bytes + array values are in bytes
    whichColor = random(arraySize);
    color = cWhites[whichColor]; // get random color from color array      
    strip3.setPixelColor(pos, color);
  }
 
  strip1.show();
  strip2.show();
  strip3.show();
}


// Flash (howmany) number of pixels, randomly, same number of pixels lit up on each star string
void flashRandom(uint8_t howmany) {
  
  int arraySize;
  int whichColor;
  uint32_t color;
  
  lightsOut();
  
  for(uint16_t i=0; i<howmany; i++) {
    // pick a random color out of array
    arraySize = sizeof(cReds)/4; // divide by 4 b/c size returned in bytes + array values are in bytes
    whichColor = random(arraySize);
    color = cReds[whichColor]; // get random color from color array
    
    // get a random pixel from the list
    int j_1 = random(strip1.numPixels());
    int j_2 = random(strip2.numPixels());
    int j_3 = random(strip3.numPixels());
      
    strip1.setPixelColor(j_1, color);
    strip2.setPixelColor(j_2, color);
    strip3.setPixelColor(j_3, color);

    strip1.show();
    strip2.show();
    strip3.show();
  }
}


// Clear each star/pixel
void lightsOut() {
  
  int arraySize_max;
  uint32_t color = 0; // no color

  arraySize_max = max((starCount_strip1,starCount_strip2),starCount_strip3);
  
  for (int pos = 0; pos < arraySize_max; pos ++) {
        strip1.setPixelColor(pos, color);
        strip2.setPixelColor(pos, color);
        strip3.setPixelColor(pos, color);
  }
  
  strip1.show();
  strip2.show();
  strip3.show();
}
