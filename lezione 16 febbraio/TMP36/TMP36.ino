
const int sensorPin = A0;
void setup() {
  // open a serial connection to display values
  Serial.begin(9600);
}

void loop() {
  // read the value on AnalogIn pin 0
  // and store it in a variable
  int sensorVal = analogRead(sensorPin);

  // send the 10-bit sensor value out the serial port
  Serial.print("sensor Value: ");
  Serial.print(sensorVal);
  // convert the ADC reading to voltage
  float voltage = (sensorVal / 1024.0) * 5.0;
  // Send the voltage level out the Serial port
  Serial.print(", Volts: ");
  Serial.print(voltage);
  // convert the voltage to temperature in degrees C
  // the sensor changes 10 mV per degree
  // the datasheet says there's a 500 mV offset
  // ((volatge - 500mV) times 100)
  Serial.print(", degrees C: ");
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);

  delay(1);
}
