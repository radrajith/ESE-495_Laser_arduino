
///***************************
// *Analog pins  
// *A2 = used as Gnd
// *A3 = used as vcc
// *A4 = SDA for DAC, LCD      //i2c communication
// *A5 = SCL for DAC, LCD      //i2c communication
// *
// *Digital Pins
// *D2 = blutooth transmit
// *D3 = bluetooth receieve 
// *D4 = SCl for tempsensor
// *D5 = SDA for tempSensor
// *D6 = Pushbutton
// *D7 = LED
// ************************************/
//
//

#include <SoftwareSerial.h>
#include <Wire.h>
#include "MLX90615.h"
#include <I2cMaster.h>
#include <string.h>
#include <rgb_lcd.h>
#include <SqWaveGen.h>
#include <Utility.h>
#include <TimedAction.h>
#define SDA_pin 5             //digital pin 5      - i2c SDA
#define SCL_pin 4             //digital pin 4      - i2c SCL
const int LED = 7;        //digital pin 7     - LED
const int button = 6;     //digital pin 6     - Button
int bluetoothTx = 3;      //digital pin 3     - bluetooth transmit
int bluetoothRx = 2;      //digtall pin 2     - bluetooth receive
int buttonState = 0;
int period = 0;
int duty = 0;
int pulses = 0;
double peak = 0;          //temporarily setting at 3v, have to code in the android app. 
char toSend = 'start up';
int num=0; 
String out;
bool once = false;
SoftI2cMaster i2c(SDA_pin, SCL_pin);
MLX90615 tempSensor(DEVICE_ADDR, &i2c);
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
SqWaveGen sqwavegen = SqWaveGen();
rgb_lcd lcd;
bool run = true;
//TimedAction lcdThread = TimedAction(100, lcdUpdate);

void setup()
{
  sqwavegen.generate(0, false);
  pinMode(A2, OUTPUT);              //for dac
  pinMode(A3, OUTPUT);
  pinMode(A0, OUTPUT);          //for Temp sensor
  digitalWrite(A0, HIGH);     //make 
  digitalWrite(A2, LOW);//Set A2 as GND
  digitalWrite(A3, HIGH);//Set A3 as Vcc //for dac
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);     //Setup usb serial connection to computer
  bluetooth.begin(9600);  //Setup Bluetooth serial connection to android
  Wire.begin();
}

void loop()
{
  //sqwavegen.generate(0, false);
  while(bluetooth.available())    //Read from bluetooth and write to usb serial
  {
    if(run){
      run = false;
      lcd.clear();
    }
      int test = bluetooth.read();
      once = true;
      out += (char) test;
      //Serial.println("line 77");
  }
  run = true;
  
  if(once){
   
    periodFind((String) out);
    String st1 = String(period) +","+String(duty)+","+String(pulses)+","+String(peak);
    lcd.print(st1);
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
  rgbColorSet(objTemp.toFloat());
  int temp1 = micros();
  delay(100);
  int temp2 = micros();
  Serial.println(temp2-temp1);

}

  delay(200);
}




void pulseGen(){
  int onTime = ((period*duty)/100);
  int offTime = period - onTime;
  Serial.println(onTime);
  for(int i = pulses; i>0; i--){
    digitalWrite(LED, HIGH);
    sqwavegen.generate(peak, false);
    delay(onTime);
   digitalWrite(LED, LOW);
   sqwavegen.generate(0, false);
    delay(offTime);
  }
}

//void pulsewavegen(double voltage){
//   Wire.beginTransmission(0x62);
//    Wire.write(0x40);         //DAC write
//    Wire.write(voltage >> 4); //write 8 msb
//    Wire.write((voltage &  15) << 4); //write 4 lsb along with 0000 at the end
//    Wire.endTransmission();
//}

void periodFind(String output){
  int one = output.indexOf(',');
  int two = output.indexOf(',', one+1);
  int three = output.indexOf(',', two+1);
  int four = output.length();
  period = (output.substring(0, one)).toInt();
  duty = (output.substring(one+1, two)).toInt();
  pulses = (output.substring(two+1, three)).toInt();
  peak = (output.substring(three+1, four)).toFloat();
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

