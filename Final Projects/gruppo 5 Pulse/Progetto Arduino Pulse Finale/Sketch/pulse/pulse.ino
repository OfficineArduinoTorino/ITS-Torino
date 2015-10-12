/*
 This sketch imports an analogic input from the ECG sensors
 into an HTML page where is shown your heartbeat
 This code is a merge of Matteo Loglio's code findable here
 https://github.com/mat-lo/yun-examples/tree/master/analogInputs
 and the eHealth library of CookingHacks findable here
 http://www.cooking-hacks.com/documentation/tutorials/ehealth-v1-biometric-sensor-platform-arduino-raspberry-pi-medical/
*/

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <eHealth.h>


int cont = 0;

YunServer server;
String startString;

void setup() {
  Serial.begin(115200);
  Serial.print("opening serial communication");

  //initialize bridge
  Bridge.begin();

  //start local server
  server.listenOnLocalhost();
  server.begin();
}

void loop() {

  YunClient client = server.accept();

  if (client) {
    String command = client.readString();
    command.trim();
    if (command == "inputs") {

      //int lightVal = analogRead(A0);


      //init JSON data
      client.println("Status:200");
      client.println("content-type:application/json");
      client.println();
      client.println("{");

      /*
      loop through the analog pins and for each pin,
      make a JSON line, like:
      "A0" : 450
      */
      //for(int i = 0; i <= 5; i++) {
      client.print("\"A");
      client.print(0);
      client.print("\":");
      //if (i == 5) {
      //int dato_1 = map(eHealth.getBPM(), 0, 5, 0, 1024);
      client.println(eHealth.getECG() * 10);
      client.println(",");
      client.print("\"A");
      client.print(1);
      client.print("\":");
      client.println(eHealth.getOxygenSaturation());
      //}
      //else {
      //  client.print(analogRead(i));
      //  client.println(",");
      //}
      //}

      //close
      client.println("}");
    }

    float ECG = eHealth.getECG() * 10;

    Serial.print("ECG value :  ");
    Serial.print(ECG, 2);
    Serial.print(" V");
    Serial.println("");

    delay(200);

    client.stop();
  }

  delay(50); // Poll every 50ms
}
