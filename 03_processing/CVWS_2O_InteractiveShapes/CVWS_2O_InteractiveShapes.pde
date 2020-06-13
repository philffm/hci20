//setup canvas
void setup() {
  size(640, 480);
  background(0);
}

//define colors used  
color nightblue = color(25, 25, 112);
color skyblue = color(135, 206, 235);
float startPosition = random(300);


void draw() {
  float wBuilding = (mouseX-startPosition);
  float hBuilding = (-mouseY+height);
  drawSky();
  drawBuilding(wBuilding,hBuilding);
  drawWindows(hBuilding);
}


void drawSky(){
  if (mousePressed){
    background(nightblue);
    for(int i=0; i < 100; i++){
      stroke(255,255,0);
      strokeWeight(2);
      point(random(width), random(width));
      frameRate(15);
  }
  }else{
    background(skyblue);
    noStroke();
    fill(240);
    frameRate(10);
    for(int iCloud=0; iCloud < 20; iCloud++){
          fill(random(220,255),random(150,255));
          rect(random(640),random(0,120),random(30,100),random(20,60),random(20,60));
      frameRate(5);

      }
  }
}
// generate window pattern

void drawWindows (float hBuilding) {

  for (float yWd=height-hBuilding;yWd<height;yWd +=20){
   for (float xWd=startPosition;xWd<mouseX;xWd +=20){
     point (xWd,yWd);
     }
    }

}

// draw building
void drawBuilding(float wBuilding, float hBuilding) {
  println(startPosition);
  fill(120); 
  rect(startPosition,height-hBuilding, wBuilding, hBuilding);

// generate window pattern
  for (float yWd=height-hBuilding;yWd<height;yWd +=20){
   for (float xWd=startPosition;xWd<mouseX;xWd +=20){
     point (xWd,yWd);
     }
    }

}
