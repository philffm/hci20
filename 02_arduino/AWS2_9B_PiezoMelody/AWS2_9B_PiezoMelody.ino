int speakerPin = 8;
void setup() { 
    pinMode(speakerPin, OUTPUT);
}
void loop() { 
    tone(speakerPin, 262, 200); 
    tone(speakerPin, 294, 200); delay(250);
    tone(speakerPin, 330, 200); delay(250);
    tone(speakerPin, 262, 200); delay(500);
delay(250);
}