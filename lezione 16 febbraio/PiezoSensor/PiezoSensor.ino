/*
piezo like sensor
giacomo leonzi
*/
const int piezoPin = A0;
int sensorValue;
int threshold = 15;
int flag = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}


void loop() {
  sensorValue = analogRead(piezoPin);
    
  if (sensorValue >= threshold && flag == 0) {
    Serial.print("sensorValue  : ");
    Serial.println(sensorValue);
    Serial.println(" ***   *  *   *        ____/    * *  ");
    Serial.println("*      *  *         ******     *   * ");
    Serial.println("*      *  *   *     *              * ");
    Serial.println("*      ****   *     ****           * ");
    Serial.println("*      *  *   *     *            *   ");
    Serial.println("*      *  *   *     *            *   ");
    Serial.println(" ***   *  *   *     *******      O   ");
    delay(500);
    flag = 1;
  }else flag = 0;
  delay(20);        // delay in between reads for stability
}
