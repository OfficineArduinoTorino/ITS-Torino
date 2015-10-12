/*
 Simple Streetlamp
 */


const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int ledPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int ledValue;        // value read from the pot

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(analogInPin);

  Serial.print("sensor = " );
  Serial.print(sensorValue);
  Serial.print("; led = ");
  
  ledValue = 255 -  map(sensorValue, 0 ,1023, 0, 255);
  //ledValue = map(sensorValue, 0 ,1023, 255, 0);
  analogWrite(ledPin, ledValue);
  Serial.println(ledValue);
  delay(2);
}   
