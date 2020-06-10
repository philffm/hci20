#include <dht.h>
#include <MD_MAX72xx.h>

dht DHT;

#define DHT11_PIN 7
//int sensePin = A0;  //This is the Arduino Pin that will read the sensor output
//int sensorInput;    //The variable we will use to store the sensor input
//double temp;        //The variable we will use to store temperature in degrees. 


// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES	4

#define CLK_PIN   11  // or SCK
#define DATA_PIN  10  // or MOSI
#define CS_PIN    9  // or SS

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
#define  DELAYTIME  100  // delay between animations in milliseconds

 
void setup(){
  Serial.begin(9600);
  mx.begin();

}

void loop()
{
 /* sensorInput = analogRead(A0); //read the analog sensor and store it
  temp = (double)sensorInput / 1024;   //find percentage of input reading
  temp = temp * 5;                     //multiply by 5V to get voltage
  temp = temp - 0.5;                   //Subtract the offset 
  temp = temp * 100;                   //Convert to degrees 
  Serial.print("Current Temperature: ");
  Serial.println(temp); */
  
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("DHT11 Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("DHT11 Humidity = ");
  Serial.println(DHT.humidity);
  float humidityValue = DHT.humidity;
  displayRow(humidityValue);
  delay(2000);


}

void displayRow(float humidityValue){
  humidityValue = map(humidityValue, 50, 100, 0, 7);
  Serial.print("Displayed humidity ");
  Serial.println(humidityValue);
  mx.clear();
  for(humidityValue<7;humidityValue--;){
    mx.setRow(humidityValue,0xff);
  }

}

