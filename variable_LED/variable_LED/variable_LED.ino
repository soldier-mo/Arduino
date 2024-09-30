int DELAY_TIME = 1000;
int RED_PIN_1 = 2;
int YELLOW_PIN_8 = 8;
int GREEN_PIN_12 = 12;

void setup() {
  pinMode(RED_PIN_1, OUTPUT);
  pinMode(YELLOW_PIN_8, OUTPUT);
  pinMode(GREEN_PIN_12, OUTPUT);
}

void loop() {
// RED
  digitalWrite(RED_PIN_1, HIGH);
	delay(DELAY_TIME);
  digitalWrite(RED_PIN_1, LOW);

// YELLOW
  digitalWrite(YELLOW_PIN_8, HIGH);
	delay(DELAY_TIME);
  digitalWrite(YELLOW_PIN_8, LOW);

// GREEN
  digitalWrite(GREEN_PIN_12, HIGH);
	delay(DELAY_TIME);
  digitalWrite(GREEN_PIN_12, LOW);

}
