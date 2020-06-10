
int sensorValue = 0; // variable for sensor value 
int sensorPin = A0; // variable for sensor pin
int speakerPin = 8; // variable for sensor pin

void setup() {
    pinMode(sensorPin, INPUT); 
    Serial.begin(9600);
}

void loop() {
    int sensorValue = analogRead(A0); 
    sensorValue = map(sensorValue, 0, 1000, 100, 2000);
    //mapping to freq range 

    Serial.println(sensorValue);
    tone(speakerPin, sensorValue, 200);
    delay(250);
    noTone(speakerPin);
    delay(100);
}
