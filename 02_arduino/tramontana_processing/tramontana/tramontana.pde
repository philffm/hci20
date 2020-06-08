import tramontana.library.*;
import websockets.*;
Tramontana device;

void setup(){
t = new Tramontana(this,"192.168.1.17");
}


void mousePressed(){
 t.makeVibrate();
}
