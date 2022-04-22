#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SD.h> //Load SD card library
#include<SPI.h> //Load SPI Library
#include "Adafruit_BMP085.h"  // import the Pressure Sensor Library We are using Version one of Adafruit API for this sensor
Adafruit_BMP085 mySensor;  // create sensor object called mySensor
int chipSelect = 4; //chipSelect pin for the SD card Reader
File mySensorData;  
boolean button=3;
LiquidCrystal_I2C lcd(0x27, 16, 2);
float tempC;  // Variable for holding temp in C
float tempF;  // Variable for holding temp in F
void setup(void)
{
  mySensor.begin();   //initialize pressure sensor mySensor
pinMode(10, OUTPUT); 
  Serial.begin(9600);
pinMode(10, OUTPUT); //Must declare 10 an output and reserve it
SD.begin(4);
   lcd.begin(0x27,16,2); 
  dht.begin();  
  delay(2000); 
  
}

void loop()
{tempC = mySensor.readTemperature(); //  Read Temperature from BMP180
tempF = tempC*1.8 + 32.; // Convert degrees C to F
 
   lcd.clear();
    Serial.print("Temp: ");
    Serial.print(tempF);
    Serial.print(" degree F.\n");
    delay(1000);
   mySensorData = SD.open("sensor.csv", FILE_WRITE);
if (button==HIGH) {
Serial.print("Time: ");
  myTime = millis();
  
Serial.print(tempC);
delay(250); //Pause between readings.
mySensorData.print(myTime);                            //write current time.
mySensorData.print(",");                               //write a commma
mySensorData.print(tempF);                             //write temperature data to card
mySensorData.close();                                  //close the file
}
  lcdDisplay(
           
             0,
             0, 
             "Temp_Celsius: ", 
             11,
             0, 
             tempF
             );  
               
  }



void lcdDisplay(int tc, int tr, String title, int vc, int vr, float value)
{
   
   lcd.setCursor (tc,tr); 
   lcd.print(title);
   lcd.setCursor (vc,vr);
   lcd.print(value);
     for(int PositionCount=0;PositionCount<13; PositionCount++)//loop for scrolling the LCD text
  {
    lcd.scrollDisplayLeft();
    delay(150);
    }

   for(int PositionCount=0; PositionCount<29; PositionCount++)
   {
    lcd.scrollDisplayRight(); 
 delay(150);
    }
   for(int PositionCount=0; PositionCount<16; PositionCount++)//loop for scrolling the text
   {
    lcd.scrollDisplayLeft();
    delay(150);
    }

 
}
