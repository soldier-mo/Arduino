int passiveBuzz = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(passiveBuzz, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(passiveBuzz, 200);
  delay(10);
  analogWrite(passiveBuzz, 0);
  delay(10);
}
