int num = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  num = (num + 1) & 22;
  Serial.println(num);
}
