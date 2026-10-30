/***********Notice and Trouble shooting***************
1. This code is tested on Arduino Uno with Arduino IDE 1.0.5 r2 and 1.8.2.
2. Calibration of the TDS Sensor (input the following):
    enter -> enter the calibration mode
    cal:tds value -> calibrate with the known tds value(25^c). e.g.cal:707
    exit -> save the parameters and exit the calibration mode
****************************************************/


#include <EEPROM.h>
#include <SPI.h>
#include <SD.h>
#include "GravityTDS.h"
#include <DHT11.h>
#include <Wire.h>
#include <RTClib.h>


RTC_DS1307 rtc;


#define TdsSensorPin A1
GravityTDS gravityTds;


#define DHTPIN 2
DHT11 dht11(DHTPIN);


#define SD_CS 10  
File dataFile;


#define Offset 42.47


#define PH_SensorPin A0
#define LED 13
double avgValue;
float phValue;


float temperature = 25, tdsValue = 0;
int humidity = 0;




void setup()
{
 Serial.begin(115200);
 //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 
 
 if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
 //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 
 gravityTds.setPin(TdsSensorPin);
 gravityTds.setAref(5.0); 
 gravityTds.setAdcRange(1024);  
 gravityTds.begin();  


 if (!SD.begin(SD_CS)) {
    Serial.println("SD card initialization failed!");
    while (1);
   }


 Serial.println("SD card ready");


 dataFile = SD.open("tds.csv", FILE_WRITE);


   if (dataFile)
   {
    dataFile.println("DateTime,Temperature_C,Humidity_%,TDS_ppm,pH");
    dataFile.close();
   }


}


void loop()
{
 DateTime now = rtc.now();




 int airTemp;


 int result = dht11.readTemperatureHumidity(airTemp, humidity);


 if (result == 0)
 {
    temperature = airTemp;
 }
    // Reading successful
 else
 {
    Serial.println(DHT11::getErrorString(result));
 }


   // ===== (TDS SENSOR) =====
   gravityTds.setTemperature(temperature);
   gravityTds.update();
   tdsValue = gravityTds.getTdsValue();


   // ===== (pH SENSOR) =====
   int buf[10];


   for(int i=0;i<10;i++)
   {
       buf[i] = analogRead(PH_SensorPin);
       delay(10);
   }


   for(int i=0;i<9;i++)
   {
       for(int j=i+1;j<10;j++)
       {
           if(buf[i] > buf[j])
           {
               int temp = buf[i];
               buf[i] = buf[j];
               buf[j] = temp;
           }
       }
   }


   avgValue = 0;


   for(int i=2;i<8;i++)
   {
       avgValue += buf[i];
   }


   float voltage = (float)avgValue * 5.0 / 1024.0 / 6.0;
   phValue = -8.13 * voltage + Offset;


   // ===== (SERIAL OUTPUT) =====


   Serial.print("RTC: ");
   Serial.print(now.year());
   Serial.print("-");
   Serial.print(now.month());
   Serial.print("-");
   Serial.print(now.day());
   Serial.print(" ");
   Serial.print(now.hour());
   Serial.print(":");
   Serial.print(now.minute());
   Serial.print(":");
   Serial.println(now.second());
  
   Serial.print("Temp: ");
   Serial.print(temperature);
   Serial.print(" C  ");


   Serial.print("Humidity: ");
   Serial.print(humidity);
   Serial.print("%  ");
  
   Serial.print("TDS: ");
   Serial.print(tdsValue,0);
   Serial.print(" ppm");


   Serial.print("    pH: ");
   Serial.println(phValue,2);


   // ===== (SD CARD LOGGING) =====
 dataFile = SD.open("tds.csv", FILE_WRITE);


 if(dataFile)
   {
    dataFile.print(now.year());
    dataFile.print("-");


    if (now.month() < 10) dataFile.print("0");
       dataFile.print(now.month());
       dataFile.print("-");


    if (now.day() < 10) dataFile.print("0");
       dataFile.print(now.day());


       dataFile.print(" ");


    if (now.hour() < 10) dataFile.print("0");
       dataFile.print(now.hour());
       dataFile.print(":");


    if (now.minute() < 10) dataFile.print("0");
       dataFile.print(now.minute());
       dataFile.print(":");


    if (now.second() < 10) dataFile.print("0");
       dataFile.print(now.second());


       dataFile.print(",");


    dataFile.print(temperature);
    dataFile.print(",");


    dataFile.print(humidity);
    dataFile.print(",");


    dataFile.print(tdsValue,0);
    dataFile.print(",");


    dataFile.println(phValue,2);
   
    dataFile.close();
   }
 else
   {
    Serial.println("Error opening data.csv");
   }


   delay(1000);
}
