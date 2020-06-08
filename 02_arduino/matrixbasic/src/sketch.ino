#include "LedControl.h"
/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10
*/
LedControl lc = LedControl(11,10,9,1); // create a new LedControl object
void setup() {
    lc.shutdown(0,false);
    lc.setIntensity(0,8)
    lc.clearDisplay(0);
    
 // Turn matrix on, no power saving lc.setIntensity(0,8); // Set brightness to a medium value lc.clearDisplay(0); // Clear the display
}
void loop(){ 

    
    lc.setRow(0,0,B00111100); 
    lc.setRow(0,1,B01000010); 
    lc.setRow(0,2,B10100101); 
    lc.setRow(0,3,B10000001); 
    lc.setRow(0,4,B10100101); 
    lc.setRow(0,5,B10011001); 
    lc.setRow(0,6,B01000010); 
    lc.setRow(0,7,B00111100); 
    delay(1000);
    // set the first row of the matrix // set the second row of the matrix // etc.
    lc.setRow(0,0,B00111100); 
    lc.setRow(0,1,B01000010); 
    lc.setRow(0,2,B10100101); 
    lc.setRow(0,3,B10000001); 
    lc.setRow(0,4,B10011001); 
    lc.setRow(0,5,B10100101); 
    lc.setRow(0,6,B01000010); 
    lc.setRow(0,7,B00111100); 
    delay(1000);
}