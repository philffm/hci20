#include "LedControl.h"
/*
DIN connects to pin 12 CLK connects to pin 11 CS connects to pin 10
*/
LedControl lc = LedControl(11,10,9,1);

/*
const byte IMAGES[][8] = {
{
  B00000000,
  B01100110,
  B01100110,
  B00000000,
  B11000011,
  B11000011,
  B01111110,
  B00111100
},{
  B00000000,
  B01100110,
  B01100110,
  B00000000,
  B00111100,
  B01111110,
  B11100111,
  B11000011
},{
  B00000000,
  B01100110,
  B01100110,
  B00000000,
  B00000000,
  B11111111,
  B11111111,
  B00000000
}};

const int IMAGES_LEN = sizeof(IMAGES)/8;
*/

// As described in https://xantorohara.github.io/led-matrix-editor/#3c7ec3c300666600|c3e77e3c00666600|0000000000666600
const uint64_t IMAGES[] = {
  0x3c7ec3c300666600,
  0xc3e77e3c00666600,
  0x00ffff0000666600
};
const int IMAGES_LEN = sizeof(IMAGES)/8;

void setup() {
    lc.shutdown(0,false); // Turn matrix on, no power saving 
    lc.setIntensity(0,8); // Set brightness to a medium value 
    lc.clearDisplay(0); // Clear the display
    Serial.begin(9600); 
}



void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      lc.setLed(0, i, j, bitRead(row, j));
    }
  }
}
int i = 0;

void loop(){
    int sensorValue = analogRead(A0); // read sensor, 0-1023 
    Serial.println(sensorValue);
    sensorValue = map(sensorValue, 0, 1000, 0, 7);
    // remap the value 0-7. (1000 eliminates noise)
    /* Map an analog value to 8 bits (0 to 255)
    Parameters

    value: the number to map.
    fromLow: the lower bound of the value’s current range.
    fromHigh: the upper bound of the value’s current range.
    toLow: the lower bound of the value’s target range.
    toHigh: the upper bound of the value’s target range.

    
     */

    if (sensorValue>6){
        displayImage(IMAGES[0]);

    }else if (sensorValue>3){
        displayImage(IMAGES[2]);

    }else{
        displayImage(IMAGES[1]);
    }
    lc.clearDisplay(0); // Clear the display 

}