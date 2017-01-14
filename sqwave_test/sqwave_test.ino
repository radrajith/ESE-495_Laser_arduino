
///***************************
// *Analog pins  
// *A2 = used as Gnd
// *A3 = used as vcc
// *A4 = SDA for DAC      //i2c communication
// *A5 = SCL for DAC      //i2c communication
// *
// *Digital Pins
// *D6 = Pushbutton
// ************************************/
//
//
//#include <Wire.h>//Include the Wire library to talk I2C
//#define ADDRESS 0x62   
//#include <SqWaveGen.h>
//
//SqWaveGen sqwave = SqWaveGen();
//int button = 6;               //pushbutton connected to digital pin 6
//int buttonState  = 0;         //buttonState - find whether the button is pressed
//void setup()
//{
//  Wire.begin();
//  
//  sqwave.generate(0, false);    //initialize the sqwave generator to gnd.   
//  pinMode(A2, OUTPUT);          //Setup analog pins 2 and 3 to be used as an extra vcc and gnd
//  pinMode(A3, OUTPUT);
//  digitalWrite(A2, LOW);        //Set A2 as GND
//  digitalWrite(A3, HIGH);       //Set A3 as Vcc
//  Serial.begin(9600);           //setup serial port
//}
////---------------------------------------------------
//void loop()
//{
//  buttonState = digitalRead(button);
//  if(buttonState == HIGH){
//      sqwave.generate(3, false);
//      delay(10000);
//      sqwave.generate(0, false);
//      delay(5000);
//  }
//  
//}
//
//
///*************************************************************
// * Puslegen
// * generating pulse based on  the pulsewidth, period, and pulses. 
// * int onTime - ontime calculated based on the period and duty cycle
// * int offtime - offtime of the pulse
// * 
// ************************************************************/
//
//void pulseGen(){
//  int onTime = ((period*duty)/100);
//  int offTime = period - onTime;
//  Serial.println(onTime);
//  for(int i = pulses; i>0; i--){
//    digitalWrite(LED, HIGH);
//    sqwavegen.generate(voltage, false);       //set dac amplitude to high
//    delay(onTime);                            
//   digitalWrite(LED, LOW);
//   sqwavegen.generate(0, false);              //set dac amplitude to gnd
//    delay(offTime);
//  }
//}
