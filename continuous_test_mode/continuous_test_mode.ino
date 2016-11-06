const int button = 6;
int buttonState = 0;
int laser =7;
void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(laser, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(button);
  if(buttonState ==HIGH){
    digitalWrite(laser, HIGH);
  }else{
    digitalWrite(laser, LOW);
  }
}
