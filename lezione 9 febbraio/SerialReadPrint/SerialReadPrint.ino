/*
Serial read and print
*/

int incomingByte = 0; //for incoming serial data

void setup() {
  Serial.begin(9600);
}

void loop() {
  //send data only when you receive data:
  if (Serial.available() > 0) {
    //read the incoming byte:
    incomingByte = Serial.read();

    //say what you got
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}

