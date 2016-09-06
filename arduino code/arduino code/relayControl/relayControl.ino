#include <Arduino.h>

// Project Five - Relay Control
//
int relayPin = 4;

void setup()
{
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  delay(1500);
  digitalWrite(relayPin, LOW);
  delay(250);
}
void loop(){}
