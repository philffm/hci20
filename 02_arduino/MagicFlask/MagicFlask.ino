#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <NeoPatterns.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "lcdContent.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#include <avr/pgmspace.h>
#endif

void allPatterns(NeoPatterns * aLedsPtr);

NeoPatterns ring16 = NeoPatterns(16, 13, NEO_GRB + NEO_KHZ800, &allPatterns);
// onComplete callback functions

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "wnet";
const char* password = "5a299b15e8-fw";

int sPomodoroTimer=0;
bool activePomodoroTimer=false;
    
void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  delay(1000); // give me time to bring up serial monitor
  Wire.begin(5, 4);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
    }
    delay(2000); // Pause for 2 seconds
   
    // Clear the buffer.
    display.clearDisplay();
    // Draw bitmap on the screen
    display.drawBitmap(0, 0, image_data_flasqLogo, 128, 64, 1);
    display.display();
 
  
  ring16.begin(); // INITIALIZE NeoPixel pixels object (REQUIRED)
  ring16.PixelFlags |= PIXEL_FLAG_GEOMETRY_CIRCLE;
  ring16.ColorWipe(COLOR32(0, 0, 02), 50, 0, REVERSE);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("magicflask");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Serial.println(touchRead(T2));  // get value of Touch 0 pin = GPIO 4
  Serial.println(touchRead(T6));  // get value of Touch 0 pin = GPIO 4

  int flaskTouch = touchRead(T2);
  int cupTouch = touchRead(T3);

      if (flaskTouch<10 && activePomodoroTimer==false)   
    {
        Serial.println(flaskTouch);
         ring16.ColorWipe(COLOR32_GREEN, 50, 0, DIRECTION_DOWN);
         activePomodoroTimer=true;
        Serial.println("Pomodoro start"); 
        delay(10);


    }else if (flaskTouch<10 && activePomodoroTimer==true) {
        Serial.println(flaskTouch);
        ring16.ColorWipe(COLOR32_RED, 50, 0, DIRECTION_DOWN);
        activePomodoroTimer=false;
        Serial.println("Pomodoro stop"); 
        delay(10);



    }/*else if (cupTouch<10 ) {
        Serial.println("TRINK!");
       ring16.ColorWipe(COLOR32_BLUE, 100, 0, DIRECTION_DOWN);

       }*/
  delay(10);
  ring16.update();    
  ArduinoOTA.handle();
}

/*
 * Handler for all pattern
 */
void allPatterns(NeoPatterns * aLedsPtr) {

    uint8_t tDuration = 100;
    uint8_t tColor = random(255);

    if (activePomodoroTimer==true){
          aLedsPtr->RainbowCycle(tDuration / 4, (tDuration & DIRECTION_DOWN));

    }else
    {
        initMultipleFallingStars(aLedsPtr, COLOR32_WHITE_HALF, 10, tDuration / 2, 3, &allPatterns);

    }
    
}