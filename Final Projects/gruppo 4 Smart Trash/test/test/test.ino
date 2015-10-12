int inputPin = A5;
int outputPin = 3;
int distance = 0;
int limite = 250;
int time=0;
 

void setup() {
  Serial.begin(9600);  
  pinMode(outputPin, OUTPUT);
}

void loop() {
  distance = analogRead(inputPin);
  if (distance > limite){
   digitalWrite(outputPin, HIGH);
} else if (distance <= limite){
   digitalWrite(outputPin, LOW);
}
   Serial.println(distance);
}
