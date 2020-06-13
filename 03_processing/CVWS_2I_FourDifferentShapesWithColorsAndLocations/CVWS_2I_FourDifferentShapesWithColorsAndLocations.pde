
// randomize eyecolor

float er = random (80,255);
float eg = random (80,255);
float eb = random (80,255);

float br = 255-er;
float bg = 255-eg;
float bb = 255-eb;

// generic color definitions

color cyan = color(62, 103, 102);
color white = color(255);
color black = color(0);
color green = color(71,125,3);
color lips = color(150,63,7);


// setup canvas
background(br,bg,bb);
size(600,600);


// basic pepe
fill(green);
strokeWeight(5);
ellipse(height/2,width/2, 300,300);
ellipse(height/2,width/2, 300,300);
ellipse(height/1.75,width/3, 300,100);
//headparts
ellipse(height/1.5,width/3.4, 150,75);
ellipse(height/2.0,width/3.4, 150,75);


fill(er,eg,eb);

ellipse(height/1.5,width/2.5, 100 ,70);
ellipse(height/2,width/2.5, 100 ,70);

//pupills
fill(black);

ellipse(height/1.5,width/2.5, 50 ,50);
ellipse(height/2,width/2.5, 50 ,50);

//pupills-inner
fill(white);
strokeWeight(1);
ellipse(height/1.5,width/2.5, 20 ,20);
ellipse(height/2,width/2.5,20 ,20);


//lips

fill(lips);
strokeWeight(5);

ellipse(height/1.75,width/1.65, 230.0, 60);

line(height/2.3,width/1.65,height/1.37,height/1.65);
