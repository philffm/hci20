int greenLedPin = 10; int yellowLedPin = 9;
void setup() {
     pinMode(greenLedPin, OUTPUT);
     pinMode(yellowLedPin, OUTPUT);
}
void loop() { 
    for (int brightness=0; brightness <256; brightness++){
         analogWrite(greenLedPin, brightness);
         analogWrite(yellowLedPin, brightness*-1); //negate value of brightness for reverse fade
         delay(10);
    }
}
