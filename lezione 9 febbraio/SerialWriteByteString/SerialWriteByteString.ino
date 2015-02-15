/*
Serial Write Byte/String
*/
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.Write(45); // send a byte whit the value 45
  
  int byteSent = Serial.write("hello"); // send the string "hello" and return the length of the string
  delay(1);        // delay in between reads for stability
}
