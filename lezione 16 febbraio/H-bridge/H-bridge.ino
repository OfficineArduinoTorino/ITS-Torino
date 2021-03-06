/*
Example to use a L293 for invert the spinning pf a DC motor
giacomo leonzi
*/
const int buttonPin = 12;
const int enablePin = 9;
const int motor1 = 6;
const int motor2 = 5;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) digitalWrite(enablePin, HIGH);
  else digitalWrite(enablePin, LOW);
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
  } else {
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, HIGH);
  }
}
