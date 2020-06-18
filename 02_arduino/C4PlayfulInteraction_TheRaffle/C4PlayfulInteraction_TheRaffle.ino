// Program to exercise the MD_Parola library
//
// Demonstrates most of the functions of the Parola library.
// All animations can be run and tested under user control.
//
// Speed for the display is controlled by a pot on SPEED_IN analog input.
// Digital switches used for control of Justification, Effect progression,
// Pause between animations, LED intensity, Display flip, and invert mode.
// UI switches are normally HIGH.
//
// UISwitch library can be found at https://github.com/MajicDesigns/MD_UISwitch
// MD_MAX72XX library can be found at https://github.com/MajicDesigns/MD_MAX72XX
//

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <MD_UISwitch.h>

#include <Servo.h>

// CHORDS (MELODY FREQS)
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_C5  523
// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted

// MATRIX
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// ULTRASONIC
const int echoPin = 2; 
const int trigPin = 3;
int ultraDuration=0;
int ultraDistance=0;
int ultraTreshold=20;


// COIN SENSOR (SOUND)
int micPin = A0;
int micValue = 0;

// PIEZO PIN
int speakerPin = 8;


// PHOTORESOSTORS (AGE SELECTION)
int prChildPin = A1;
int prTeenPin = A2;
int prAdultPin = A3;

int childValue = 0;
int teenValue = 0;
int adultValue = 0;
// TRESHOLD Value (LIGHT TRIGGER)
int prTreshold = 0;

// HARDWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


    // Scrolling parameters

    uint8_t scrollSpeed = 25;    // default frame delay value
    textEffect_t scrollEffect = PA_SCROLL_LEFT;
    
    textPosition_t scrollAlign = PA_LEFT;
    uint16_t scrollPause = 2000; // in milliseconds

    // Global message buffers shared by Serial and Scrolling functions
    #define	BUF_SIZE	75
    char curMessage[BUF_SIZE] = { "" };
    char newMessage[BUF_SIZE] = { "Hello!" };
    bool newMessageAvailable = false;




/* PROGRESS IN JOURNEY
    0   START 
    1   COIN INSERTED
    2   SELECTED AGE (CHILD | TEEN | ADULT)
    3   WIN STATE 
*/
int journeyStep = 0; 


/* AGE MODES
    Saved as int to safe storage
    1   CHILD
    2   TEEN
    3   ADULT
*/
int ageMode = 0;

// TICKET NUMBER
int currentTicket = 0;
bool ticketDone=false;


// SERVO
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int servoPos = 90;    // variable to store the servo position
bool servoDone = false;
bool servoLoseDone = false;



// Alternative to delay function
const unsigned long eventInterval = 1000;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;


const uint16_t PAUSE_TIME = 1000; // in milliseconds
const uint8_t SPEED_DEADBAND = 5; // in analog units


// Sprite Definition
const uint8_t F_ROCKET = 2;
const uint8_t W_ROCKET = 11;
static const uint8_t PROGMEM rocket[F_ROCKET * W_ROCKET] =  // rocket
{
  0x18, 0x24, 0x42, 0x81, 0x99, 0x18, 0x99, 0x18, 0xa5, 0x5a, 0x81,
  0x18, 0x24, 0x42, 0x81, 0x18, 0x99, 0x18, 0x99, 0x24, 0x42, 0x99,
};

// Global variables
uint8_t	curString = 0;
const char *msg[] =
    {
    "Parola for",
    "Arduino",
    "LED Matrix",
    "Display"
    };
#define NEXT_STRING ((curString + 1) % ARRAY_SIZE(msg))


void readSerial(void)
{
  static char *cp = newMessage;

  while (Serial.available())
  {
    *cp = (char)Serial.read();
    if ((*cp == '\n') || (cp - newMessage >= BUF_SIZE-2)) // end of message character or full buffer
    {
      *cp = '\0'; // end the string
      // restart the index for next filling spree and flag we have a message waiting
      cp = newMessage;
      newMessageAvailable = true;
    }
    else  // move char pointer to next position
      cp++;
  }
}

void setup () 
{
    // SOUNDDETECTION
    pinMode(micPin, INPUT);
    // PHOTORESISTORS
    pinMode(prChildPin, INPUT);
    pinMode(prTeenPin, INPUT);
    pinMode(prAdultPin, INPUT);
    // ULTRASONIC
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    // SERVO
    myservo.attach(6);  // attaches the servo on pin 9 to the servo object


    pinMode(speakerPin, OUTPUT);
    // Parola object
    P.begin();
    P.setSpriteData(rocket, W_ROCKET, F_ROCKET, rocket, W_ROCKET, F_ROCKET);
    P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);

    childValue = analogRead(prChildPin);
    teenValue = analogRead(prTeenPin);
    adultValue = analogRead(prAdultPin);
    int minTreshold = min(min(childValue,teenValue),adultValue);
    prTreshold = minTreshold * 0.9;
    //prTreshold = round(((childValue+teenValue+adultValue)/3)*0.9);
    //int prTreshold = int(analogRead(prChildPin))-15;
    //int prTreshold = round(((analogRead(prChildPin)+analogRead(prTeenPin)+analogRead(prAdultPin))/3))-30;
    Serial.begin (9600);


}
 
void loop () 
{  
  // DELAY ALTERNATIVE, UPDATES FREQUENTLY
  currentMillis = millis();
  if((unsigned long)(currentMillis-previousMillis) >= eventInterval*2){
    Serial.println("Timer gehhht");
    Serial.println("PR Treshold: " + String(prTreshold) + " "+ String(analogRead(prChildPin))+String(analogRead(prTeenPin))+String(analogRead(prAdultPin)));

    previousMillis = currentMillis;
  }


  goMachine();
  if (P.displayAnimate())
  {
    if (newMessageAvailable)
    {
      strcpy(curMessage, newMessage);
      newMessageAvailable = false;
    }
    P.displayReset();
  }
  readSerial();
}


void goMachine(){
    
  // JOURNEY STEP 0 - IDLE - INSERT CASH
  if(journeyStep == 0){
      micValue = analogRead(A0);
     // Serial.println(micValue);
      char newMessage[BUF_SIZE] = { "GIB MIR 1 GELD" };
      newMessageAvailable = true;
      strcpy(curMessage, newMessage);
      if (micValue >=70 ) {
        playTone(1,true);
        journeyStep++;
    }
  // JOURNEY STEP 1 - AGE SELECT
  }else if (journeyStep == 1){
    bool confirmationDone = false; 
    char newMessage[BUF_SIZE] = { "WIE ALT BIST DU?" };
    newMessageAvailable = true;
    strcpy(curMessage, newMessage);

    childValue = analogRead(prChildPin);
    teenValue = analogRead(prTeenPin);
    adultValue = analogRead(prAdultPin);

    if (childValue  <= prTreshold | teenValue  <= prTreshold | adultValue  <= prTreshold  ) {
        if (childValue  <= prTreshold ) {
        playTone(2,true);
        ageMode = 1;
      }else if (teenValue  <= prTreshold) {
        playTone(2,true);
        ageMode = 2;
      }else if (adultValue  <= prTreshold) {
        playTone(2,true);
        ageMode = 3;
      }
    }

    if (ageMode>=1) {
      journeyStep++;
    }
      
    }
  // JOURNEY STEP 2 - CONFIRMATION 
   else if (journeyStep == 2) {

          
    if (ageMode == 1) {
      char newMessage[BUF_SIZE] = { "OH, EIN KIND!" };
      newMessageAvailable = true;
      strcpy(curMessage, newMessage);
      
    }else if (ageMode == 2) {
      char newMessage[BUF_SIZE] = { "OH, EIN TEENAGER!" };
      newMessageAvailable = true;
      strcpy(curMessage, newMessage);

    }else if (ageMode == 3) {
      char newMessage[BUF_SIZE] = { "OH, EIN ERWACHSENER!" };
      newMessageAvailable = true;
      strcpy(curMessage, newMessage);
     }
      
      char newMessage[BUF_SIZE] = { "OK, SCHWINGE DEN ZAUBERSTAB!" };
      newMessageAvailable = true;
      strcpy(curMessage, newMessage);
    
      ultraDistance = calcDistance(3);
    
      if (ultraDistance <= ultraTreshold){
        journeyStep++;Serial.println("Level Up" + journeyStep);
      }

    }
  
    // JOURNEY STEP 3 - SPIN DAT WHEEL
  else if (journeyStep == 3) {

      if(ticketDone == false) {
        currentTicket = randomTicket();
        if(currentTicket >= 1){
          Serial.println(currentTicket);
          ticketDone = true;
        } 
      }else if (servoDone == false){
        int niete = 170;
        int gewinn = 0;
        //+ char(currentTicket)
        if(servoLoseDone == false){
          for (servoPos = 90; servoPos <= niete; servoPos += 1) { // goes to lose position
            // in steps of 1 degree
            myservo.write(servoPos);              
            delay(30);         
            if(servoPos==niete){
              servoLoseDone = true;
            }              
          }
        }else if (servoLoseDone == true){
          for (servoPos = 180; servoPos >= gewinn; servoPos -= 1) { // goes to win position
            if (servoPos == gewinn) {
              servoDone = true;
              }else {
                myservo.write(servoPos);             
                delay(15);
              }
          }
        }
          
          
        }
         else if (servoDone == true) {
            newMatrixText("GEWINNER");
        }
      
    }


    
  

}

void playTone(int toneID, bool playState){
  
  if (toneID == 1 && playState==true)  {
    delay(500);
    tone(speakerPin, NOTE_C5, 500); 
    delay(500);
    //Hallelujah melody 
    tone(speakerPin, NOTE_G4, 250); delay(250);
    tone(speakerPin, NOTE_A4, 250); delay(250);
    tone(speakerPin, NOTE_G4, 250); delay(250);
    playState = false;

  }else if (toneID == 2 && playState==true){
    tone(speakerPin, NOTE_G4, 250); 
    tone(speakerPin, NOTE_A4, 250); 
    playState = false;

  }

        
}


int calcDistance(int intervals) {
  int sum = 0;
  for (int i = 0; i <= intervals; i++) {
    //https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    ultraDuration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    ultraDistance = ultraDuration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    sum += ultraDistance;
  }
  int average = sum / intervals;
  return average;
}

int randomTicket(){
   return random(300);  
}

void newMatrixText(String text) {

  int str_len = text.length() + 1; 
  // Prepare the character array (the buffer) 
  char char_array[str_len];
  text.toCharArray(char_array, str_len);
  
  char newMessage[BUF_SIZE] =  {char_array[str_len]} ;
  newMessageAvailable = true;
  strcpy(curMessage, newMessage);  
}