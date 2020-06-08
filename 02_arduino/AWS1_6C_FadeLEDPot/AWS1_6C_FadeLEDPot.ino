float sensorValue = 0; // variable for sensor value 
int sensorPin = A0; // variable for sensor pin
int greenLedPin = 10; int yellowLedPin = 9;

void setup() {
    sensorValue = (sensorValue/1023)*255;
    pinMode(sensorPin, INPUT);
    Serial.begin(9600);
    pinMode(greenLedPin, OUTPUT);
    pinMode(yellowLedPin, OUTPUT);

}

void loop() {
    sensorValue = analogRead(sensorPin); // read the value/voltage on the sensor pin and // store that value in the variable sensorValue
    sensorValue = (sensorValue/1023)*255;
    analogWrite(greenLedPin, sensorValue);
    analogWrite(yellowLedPin, sensorValue*-1);
    Serial.println(sensorValue); // print out sensorValue to the Serial Monitor
    delay(200); // delay for 0.2 seconds
}
