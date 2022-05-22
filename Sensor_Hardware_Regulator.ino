/*-----Import Libraries-------*/
#include "DHT.h"
#include <Arduino.h>
#include <U8x8lib.h>

#define DHTPIN 3             // temperature sensor location
#define DHTTYPE DHT11       // temperature sensor type
#define REDLED 4
#define SOUND A2           //Sound sensor
#define soundLevel 500     //The sound threshhold
#define MOSFET 2           // The heater

DHT dht(DHTPIN, DHTTYPE);

unsigned long ct = millis();
unsigned long st = 0;
const long et = 750;


auto display = U8X8_SSD1306_128X64_NONAME_HW_I2C(U8X8_PIN_NONE);


void setup() {
  Serial.begin(9600);
  dht.begin();                 // initialize the temperature sensor
  
  /*sound sensor*/
  pinMode(SOUND, INPUT);
  pinMode(REDLED, OUTPUT);

  display.begin(); // starts up OLED display
  display.setFlipMode(1);
  display.clearDisplay();
  display.setFont(u8x8_font_7x14B_1x2_r);
  
  pinMode(LED_BUILTIN, OUTPUT);
}


/*----------Method for the Heater-----------*/
 void controlforHeater(){
   int tempC = dht.readTemperature();           //Reads temperature from sensor
   const auto receivedTemp = Serial.read();     //Receives requested temperature from Java
   const int requestedTemp = receivedTemp;      //Stores requested temperature as integer

     if(tempC <= requestedTemp && REDLED == HIGH){
       display.println(tempC);
       delay(1000);
       display.clearDisplay();
       display.setCursor(0,0);
       digitalWrite(MOSFET,HIGH);
    }
    else if(tempC <= requestedTemp){
       display.print(tempC);
       delay(1000);
       display.clearDisplay();
       display.setCursor(0,0);
       digitalWrite(MOSFET,HIGH);
    }
    else{
      display.print(tempC);
       delay(1000);
       display.clearDisplay();
       display.setCursor(0,0);
      digitalWrite(MOSFET,LOW);
    }
 }



 /*--------------The Loop--------------*/

void loop() {
  /*-----For the sound sensor----*/
int value = analogRead(SOUND);
if (value > soundLevel) {
  digitalWrite(REDLED, HIGH);
  }
  
    
if (!Serial.available()) {
        return;
        }

controlforHeater();
   
}


void temperatureMonitor() {

    int tempReading = dht.readTemperature();
    const auto graphreading = tempReading;
    const byte graphdata[] = {0,0, highByte(graphreading), lowByte(graphreading)};
    Serial.write(graphdata, 4);
    Serial.println();
  }
