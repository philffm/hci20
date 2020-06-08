#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
int greenLedPin = 10; 
int redLedPin = 9;
int sensorValue = 0; // variable for sensor value 
int sensorPin = A0; // variable for sensor pin

void setup() {
pinMode(sensorPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  Serial.begin(9600);
}
void loop() {

    sensorValue = analogRead(sensorPin);
    sensorValue = (sensorValue/1023)*255;
    Serial.println(sensorValue);
  analogWrite(greenLedPin, sensorValue);  // turn analogWrite(yellowLedPin, 128); // turn on the yellow LED half way
  delay(1000);                    // wait one second
  analogWrite(greenLedPin, sensorValue);    // turn the green LED off
  analogWrite(redLedPin, sensorValue); // turn on the yellow LED maximally
  delay(1000);                    // wait one second
}


