/*
State Change (modulo)
*/

const int buttonPin = 5;
const int ledPin = 9; 

//counter for the number of button presses
int buttonPushCounter = 0;
//current state of the button
int buttonState = 0;
//previous state of the button
int lastButtonState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop(){
  buttonState = digitalRead(buttonPin);
  
 
  //compare the buttonState to its previous state 
  if (buttonState != lastButtonState){
    //if the state has changed, increment the counter
    if( buttonState == HIGH) {
      //if the current state is HIGH then the button 
      //went from of to on
      buttonPushCounter++;
    }
  }
  //save the current state as the last state,
  //for the next time through the loop
  lastButtonState = buttonState;
  
  // turns on the LED every two button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (buttonPushCounter % 2 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
   digitalWrite(ledPin, LOW);
  }
 
}

