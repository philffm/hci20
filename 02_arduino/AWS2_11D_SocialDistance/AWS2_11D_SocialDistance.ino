#include <MD_MAX72xx.h>
const int echoPin = 6; 
const int trigPin = 7;
//int ledPin = 8;

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES	4

#define CLK_PIN   11  // or SCK
#define DATA_PIN  10  // or MOSI
#define CS_PIN    9  // or SS

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
#define  DELAYTIME  100  // delay between animations in milliseconds

void setup() {
     pinMode(echoPin, INPUT);
     pinMode(trigPin, OUTPUT);
     Serial.begin(9600); 
     //pinMode(ledPin, OUTPUT);
    mx.begin();

}

void loop() {
    // send a pulse 
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);
    // wait for the echo
    long duration = pulseIn(echoPin, HIGH);
    // convert the time into a distance, the speed of sound is 29 microseconds per centimeter,
    //the pulse traveled forth and back, so we divided the distance by 2
    int cm = duration / 29 / 2; 
    Serial.print(cm);
    Serial.println();
    displayRow(cm);

    delay(100); 
}

void displayRow(int distanceValue){
  distanceValue = map(distanceValue, 2, 150, 7, 0);
  Serial.print("Displayed VALUE ");
  Serial.println(distanceValue);
  mx.clear();
  if(distanceValue>6){

    mx.setRow(0,B10011001);
    mx.setRow(1,B10011001);
    mx.setRow(2,B10011001);
    mx.setRow(3,B10011001);
    mx.setRow(4,B10011001);
    mx.setRow(5,B10011001);
    mx.setRow(6,B00000000);
    mx.setRow(7,B10011001);

        delay(1000);

    }
  for(distanceValue<7;distanceValue--;){
    mx.setRow(distanceValue,0xff);
  }

    
}

