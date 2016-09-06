#include <Arduino.h>

#include <SoftwareSerial.h>
#include "MLX90615.h"
#include <I2cMaster.h>
#include <string.h>
#define SDA 5
#define SCL 4
int bluetoothTx = 3;
int bluetoothRx = 2;

SoftI2cMaster i2c(SDA, SCL);
MLX90615 tempSensor(DEVICE_ADDR, &i2c);
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
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
    char toSend = (char)bluetooth.read();
    Serial.print(toSend);
  }
/*
  //Read from usb serial to bluetooth
  if(Serial.available())
  {
    char toSend = (char)Serial.read();
    bluetooth.print(toSend);
   
  }
  */
{
  
  String objTemp = (String)(tempSensor.getTemperature(MLX90615_OBJECT_TEMPERATURE));
  String ambTemp = (String)(tempSensor.getTemperature(MLX90615_AMBIENT_TEMPERATURE));
  String temp = "  " + objTemp + "  ";
  char arr[18];
  temp.toCharArray(arr,18);
  Serial.println(arr);
  bluetooth.write(arr);
  //bluetooth.write(";");
  
}
  
  delay(1000);
}
