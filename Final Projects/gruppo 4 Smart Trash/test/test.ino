int input1Pin = A5;
int output2Pin = 3;
int distance = 0;
int reading = 0;
int limite = 400;

void setup() {
  Serial.begin(9600);  
  pinMode(output2Pin, OUTPUT);

}

void loop() {
 distance = analogRead(input1Pin);
// if (distance > limite){
//   digitalWrite(output2Pin, HIGH);
// } else if (distance <= limite){
//   digitalWrite(output2Pin, LOW);
// }
reading = map(distance, 0, 600, 0, 255);
analogWrite(output2Pin, reading);
 Serial.println(distance);
}

//void getDistance() {
//
//  intensity = 0;
//
//  digitalWrite(emitterPIN, LOW); // Lettura ambientale
//
//  for(int i = 0; i < readings; i++) {
//
//    ambient = ambient + analogRead(inputPIN);
//
// }
//
//  digitalWrite(emitterPIN, HIGH); // Lettura attiva
//
//  for (int i = 0; i < readings; i++) {
//
//  intensity = intensity + analogRead(inputPIN);
// }
