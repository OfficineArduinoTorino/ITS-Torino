int inputPin = A5;
int outputPin = 3;
int distance = 0;
int limite = 100;
long int time=0;
boolean flag=false;
int range=2000;
 

void setup() {
  Serial.begin(9600);  
  pinMode(outputPin, OUTPUT);
}

void loop() {
  distance = analogRead(inputPin);
  if (distance > limite && flag==false){
    time= millis();
    flag=true;
    }
 else if (distance <= limite){
   digitalWrite(outputPin, LOW);
   flag=false;
}
if(time+range<millis() && flag==true){
 digitalWrite (outputPin,HIGH); 
   
   }
Serial.println(distance);
}

