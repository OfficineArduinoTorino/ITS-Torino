/*
Fade
*/
int led = 13;
int brightness = 0;  //how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  //set brightness of pin 9
  analogWrite(led, brightness);

  //change the brightness for next time throught the loop:
  brightness = brightness + fadeAmount;

  //reverse the direction of fading at the ends
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount;
  }
  delay(30);
}
