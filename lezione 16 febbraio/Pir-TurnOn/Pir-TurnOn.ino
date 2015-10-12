const int pirPin = 10;
const int ledPin = 6;
int latency = 2000;
int event;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int pirState = digitalRead(pirPin);
  if (pirState != 0){
  Serial.println(pirState);
  digitalWrite(ledPin, HIGH);
  event = millis();
  }
  if (pirState == 0 && (event + latency >= millis())){
    Serial.println(pirState);
  digitalWrite(ledPin, LOW);
  }
  delay(1);        // delay in between reads for stability
}



