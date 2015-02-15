/*
State Change
*/

const int buttonPin = 5;
const int ledPin = 9; 

int buttonState = 0;
int buttonFlag = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop(){
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH){
    //if the pushbutton, check buttonFlag
    if( buttonFlag == 1){
      buttonFlag = 0;
      digitalWrite(ledPin, LOW);
      delay(500); //to avoid bouncing
    }
    else{
      buttonFlag = 1;
      digitalWrite(ledPin, HIGH);
      delay(500); //to avoid bouncing
    }
  }
}
