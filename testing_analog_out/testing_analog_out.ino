int aout =9;
void setup() {
  // put your setup code here, to run once:
  pinMode(aout, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(aout, 153);
  delay(10000);
  //analogWrite(aout,0);
  //delay(5000);
}
