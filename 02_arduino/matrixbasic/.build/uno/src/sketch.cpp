#include <Arduino.h>
#include "LedControl.h"
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include "LedControl.h"
/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10
*/
LedControl lc = LedControl(11,10,9,1); // create a new LedControl object
void setup() {
    lc.shutdown(0,false);
    lc.setIntensity(0,8);
    lc.clearDisplay(0);
    Serial.begin(9600);

    
 // Turn matrix on, no power saving lc.setIntensity(0,8); // Set brightness to a medium value lc.clearDisplay(0); // Clear the display
}
void loop(){ 

    int sensorValue = analogRead(A0); // read sensor, 0-1023 Serial.println(sensorValue);
    sensorValue = map(sensorValue, 0, 1000, 0, 7);
    
    // remap the value 0-7. (1000 eliminates noise)
    lc.clearDisplay(0); // Clear the display l
    lc.setRow(0, sensorValue, B11111111); // Turn one line on
    Serial.println (sensorValue);
    delay(20);
}