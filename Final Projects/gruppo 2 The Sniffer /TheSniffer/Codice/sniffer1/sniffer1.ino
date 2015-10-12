// These constants won't change.  They're used to give names
// to the pins used:
const int analogOutPin = 11; // Analog output pin that the LED is attached to

unsigned long int _speed=0;
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0){ //if there is anything on the serial port, read it
        _speed = (unsigned long int)Serial.parseInt(); //store it in the _speed variable
        
    if (_speed > 0) {
      // map it to the range of the analog out:
      if (_speed>250000) _speed=250000;
      outputValue = map(_speed, 0, 250000, 0, 255);
      // change the analog out value:
      analogWrite(analogOutPin, outputValue);
  
      // print the results to the serial monitor:
      Serial.print("speed = " );
      Serial.print(_speed);
      Serial.print("\toutput = ");
      Serial.println(outputValue);
  
      // wait 2 milliseconds before the next loop
      // for the analog-to-digital converter to settle
      // after the last reading:
       } 
    }
    Serial.println(_speed);
    Serial.println(outputValue);
    delay(2);
}
