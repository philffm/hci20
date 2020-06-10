import processing.serial.*;
Serial myPort;
String sensorReading="";

void setup() {
  size(400, 400);
  myPort = new Serial(this, Serial.list()[4], 9600); 
  // instead of 5, choose what everserial port the Arduino connects to
  myPort.bufferUntil('\n'); }
  
  void draw() {
  int sensorReadingNum = Integer.parseInt(sensorReading.trim());  
  int sensorReadingNeg =   (sensorReadingNum*-1)+200;

  background(255);
  
  fill(0,128,255);
  textSize(12);

  text("Sensor Reading: " + sensorReading, 20, 20);
  
  rectMode(CENTER);
  rect(width/2, height/2, float(sensorReadingNeg*2), float(sensorReadingNeg), 9);
  textSize(32);
  fill(255, 255, 255);
  textAlign(CENTER);{

  if(sensorReadingNum<20) {
  text("AFSTAND HOUDEN!", width/2, height/2);}

    }
  }
  void serialEvent (Serial myPort) { sensorReading = myPort.readStringUntil('\n');
}
