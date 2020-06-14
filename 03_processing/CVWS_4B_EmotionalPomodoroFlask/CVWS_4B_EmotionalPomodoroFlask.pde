import processing.serial.*;
Serial myPort;
String sensorReading="";
PImage img;
String flasqImages[] = split("idleflasq.png,pomodoroflasq.png,sadflasq.png", ',');
String currentFlasq = "idleflasq.png";
String flasqStatus = "idle";
int t;
int interval = 310;
int timerStart, timerPomodoro;
String time = "010";

void setup() {
  size(400, 400);
  myPort = new Serial(this, Serial.list()[4], 115200); 
  // Baud rate is different on ESP32
  myPort.bufferUntil('\n'); 
  img = loadImage(currentFlasq);
  timerStart=millis();
  println(timerStart);

  
}

  void draw() {

  background(48,52,55);
  image(img,100,100,img.height,img.width);

  fill(0,128,255);
  textSize(12);
    text("Sensor Reading: " + sensorReading, 20, 20);


 if(sensorReading.indexOf("start") >= 0){
        currentFlasq="pomodoroflasq.png";
        img = loadImage(currentFlasq);
        flasqStatus = "pomodoro";



  }else if(sensorReading.indexOf("stop") >= 0){
        currentFlasq="sadflasq.png";
        img = loadImage(currentFlasq);

  }else if (flasqStatus== "idle") {
          currentFlasq="idleflasq.png";
        img = loadImage(currentFlasq);

  
  }if (flasqStatus == "pomodoro") {
            fill(255);
          timerPomodoro =  millis() - timerStart;

          t = interval-int(timerPomodoro/1000);
          time = nf(t , 3);
          if(t == 0){
            println("POMODORO STOP");
          interval+=10;}
          textAlign(CENTER);
          textSize(32);
          text(time, width/2, 0.95*height);
       }else {
         
         
       }
  rectMode(CENTER);
  //rect(width/2, height/2, float(sensorReadingNeg*2), float(sensorReadingNeg), 9);
  textSize(32);
  fill(255, 255, 255);
  textAlign(CENTER);{

    }
  }
  void serialEvent (Serial myPort) { sensorReading = myPort.readStringUntil('\n');
}
