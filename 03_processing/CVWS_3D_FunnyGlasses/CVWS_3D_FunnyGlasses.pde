import gab.opencv.*;
import java.awt.Rectangle;

OpenCV opencv;
PImage img;
Rectangle[] faces;

String funnyGlassesFiles[] = split("dealwithit.png,versace.png,mafia.png", ',');
String currentGlasses = funnyGlassesFiles[(int)random(funnyGlassesFiles.length)];

void setup() {
  background(0);
  opencv = new OpenCV(this, "friends.jpg");
  size(1200 , 720);
  opencv.loadCascade(OpenCV.CASCADE_FRONTALFACE);  
  faces = opencv.detect();
  println(currentGlasses);
  img = loadImage(currentGlasses);

}



void draw() {
 
    image(opencv.getInput(), 0, 0);

  for (int i = 0; i < faces.length; i++) {
    image(img, faces[i].x, faces[i].y*1.15,faces[i].width, faces[i].height/2);  }
    
}
