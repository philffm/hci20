
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#include <avr/pgmspace.h>
#endif
#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const long oneSecond = 1000; // a second is a thousand milliseconds
int sensorPin=10;
boolean sensorVal =0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char productInventory[] = {'Doener', 'Handyvertrag', 'Suppe'};
const byte productInventoryLength = sizeof(productInventory) / sizeof(productInventory[0]);
char currentProduct=0;  //allow 1 extra for the NULL
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



int data = 11;    // DIN pin of MAX7219 module
int load = 9;    // CS pin of MAX7219 module
int clock = 10;  // CLK pin of MAX7219 module

int maxInUse = 4;  //how many MAX7219 are connected

MaxMatrix Matrix(data, load, clock, maxInUse); // define Library
byte buffer[10];

char string1[] = " Brainy-Bits.com      ";  // Scrolling Text


void setup() {
  Matrix.init(); // MAX7219 initialization
  Matrix.setIntensity(8); // initial led matrix intensity, 0-15
 
  Serial.begin(9600);
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.
  pinMode(sensorPin, INPUT);

}

void writeProduct() {
 
    currentProduct = productInventory[random(0, productInventoryLength)];
    lcd.setCursor(0, 0);
    lcd.print(currentProduct);
    Serial.print(currentProduct);
    delay(oneSecond);

}
void writePrice() {
 
    lcd.setCursor(0, 1);
    lcd.print("FRISCH!");
    delay(oneSecond);
    lcd.setCursor(0, 1);
    lcd.print("JETZT KAUFEN!");
    delay(oneSecond);

}


void loop() {
  runMatrix();
  writeProduct();  
  writePrice();
  runLED();
  
}

