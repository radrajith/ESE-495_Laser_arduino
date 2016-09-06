#include <SoftwareSerial.h>
#include <Wire.h>
#include "MLX90615.h"
#include <I2cMaster.h>
#include <string.h>
#include <rgb_lcd.h>
#define SDA 5
#define SCL 4
int bluetoothTx = 3;
int bluetoothRx = 2;
char toSend = 'start up';

SoftI2cMaster i2c(SDA, SCL);
MLX90615 tempSensor(DEVICE_ADDR, &i2c);
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
rgb_lcd lcd;
bool run = true;
void setup()
{
  
  lcd.begin(16, 2);
  //lcd.setRGB(255,0,0);
  //Setup usb serial connection to computer
  Serial.begin(9600);
  //Setup Bluetooth serial connection to android
  //bluetooth.begin(9600);
  //bluetooth.print("AT+NAME=ese495_bt\r\n");
  //bluetooth.print("$$$");
  //delay(100);
  //bluetooth.println("U,9600,N");
  bluetooth.begin(9600);
}

void loop()
{
  
  //Read from bluetooth and write to usb serial
  while(bluetooth.available())
  {
    if(run){
      run = false;
      lcd.clear();
    }
      //lcd.setCursor(0,0);
      toSend = (char)bluetooth.read();
      Serial.print(toSend);
    //lcd.clear();
      lcd.print(toSend);
      
  }
  run = true;
/*
  //Read from usb serial to bluetooth
  if(Serial.available())
  {
    char toSend = (char)Serial.read();
    bluetooth.print(toSend);

  }
  */
{
  lcd.setCursor(0,1);
  String objTemp = (String)(tempSensor.getTemperature(MLX90615_OBJECT_TEMPERATURE));
  String ambTemp = (String)(tempSensor.getTemperature(MLX90615_AMBIENT_TEMPERATURE));
  String temp = "  " + objTemp + "  ";
  char arr[18];
  temp.toCharArray(arr,18);
  Serial.println(arr);
  //lcd.print(toSend);
 lcd.print(arr);
  bluetooth.write(arr);
  //
  rgbColorSet(objTemp.toFloat());


}

  delay(1000);
}
void rgbColorSet(double temp){
  long rgb = (temp * 131072); 
  int red = 0;
  int blue = 0;
  int green = 0;
  byte bits[24]; 
  if(rgb<=5592405){
      blue = rgb/21845;
    }
  else if(rgb < (2*5592405)){
    blue = 255;
    green = (rgb-5592405)/21845;
  }
  else if(rgb < (256*256*256)){
    blue = 255;
    green = 255;
    red = (rgb - (2*5592405))/21845;
  }
  Serial.print(temp);
  Serial.print(" ");
 // for(int i = 0; i <24 ; i++){
  Serial.print(red);
  //}
  Serial.print(" ");
  Serial.print(green);
  Serial.print(" ");
  Serial.println(blue);
  lcd.setRGB(red, green, blue);
  return 0;
}

