#include <SoftwareSerial.h>
#include <Wire.h>
#include "MLX90615.h"
#include <I2cMaster.h>
#include <string.h>
#include <rgb_lcd.h>
#define SDA 5
#define SCL 4
const int LED = 7;
const int button = 6;
int bluetoothTx = 3;
int bluetoothRx = 2;
int buttonState = 0;
int period = 0;
int duty = 0;
int pulses = 0;
char toSend = 'start up';
int num=0; 
String out;
bool once = false;
SoftI2cMaster i2c(SDA, SCL);
MLX90615 tempSensor(DEVICE_ADDR, &i2c);
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
rgb_lcd lcd;
bool run = true;
void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT);
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
      //
      run = false;
      lcd.clear();
    }
      //lcd.setCursor(0,0);
      //toSend = (char)bluetooth.read();
      int test = bluetooth.read();
      once = true;
      //toSend = (char)test;
      out += (char) test;
  }
  run = true;
  
  if(once){
    periodFind((String) out);
    String st1 = String(period) +","+String(duty)+","+String(pulses);
    //toSend = char(str1);//+','+char(duty)+','+char(pulses);
    lcd.print(st1);
    //Serial.println(st1);
    once = false;
  }
  out= " ";

  buttonState = digitalRead(button);
  if(buttonState ==HIGH){
    pulseGen();
  }
  else{
    digitalWrite(LED, LOW);
  }
  {
    lcd.setCursor(0,1);
    String objTemp = (String)(tempSensor.getTemperature(MLX90615_OBJECT_TEMPERATURE));
    String ambTemp = (String)(tempSensor.getTemperature(MLX90615_AMBIENT_TEMPERATURE));
    String temp = "  " + objTemp + "  ";
    char arr[18];
    temp.toCharArray(arr,18);
  Serial.println(arr);
  
  lcd.print(arr);
  bluetooth.write(arr);
  //
  rgbColorSet(objTemp.toFloat());


}

  delay(100);
}




void pulseGen(){
  int onTime = ((period*duty)/100);
  int offTime = period - onTime;
  //Serial.println(onTime);
  for(int i = pulses; i>0; i--){
    digitalWrite(LED, HIGH);
    //Serial.print(onTime);
    //Serial.println(offTime);
    delay(onTime);
    digitalWrite(LED, LOW);
    delay(offTime);
  }
}

void periodFind(String output){
  int one = output.indexOf(',');
  int two = output.indexOf(',', one+1);
  int three = output.length();
  period = (output.substring(0, one)).toInt();
  duty = (output.substring(one+1, two)).toInt();
  pulses = (output.substring(two+1, three)).toInt();
  //Serial.print(period);
  //Serial.print(duty);
  //Serial.println(pulses); 
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
  lcd.setRGB(red, green, blue);
  return 0;
}

