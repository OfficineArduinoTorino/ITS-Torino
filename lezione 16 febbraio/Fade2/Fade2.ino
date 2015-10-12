/* 
Fade two
*/

int ledPin = 13;

void setup() {
  }

void loop() {
 //fade in from min to max in increment of 5 points:
 for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5){
      analogWrite(ledPin, fadeValue);
   delay(30);
 }
 //fade out from max to min in increment of 5 points:
 for (int fadeValue =255; fadeValue >= 0; fadeValue -= 5){
      analogWrite(ledPin, fadeValue);
   delay(30);
 }
 
}

