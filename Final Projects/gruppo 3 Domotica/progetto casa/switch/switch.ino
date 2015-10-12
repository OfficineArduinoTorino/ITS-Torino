#include <TinkerKit.h>
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>



// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.

YunServer server;

TKRelay relay(O0);

void setup() {

  Serial.begin(9600);

  // Bridge startup

  //soggiorno
  pinMode(A2,OUTPUT);    //luce stanza [16]
  pinMode(A1,OUTPUT);    //tv          [15]
  pinMode(A0,OUTPUT);    //pc          [14]
  //cucina
  pinMode(13,OUTPUT);    //luce cucina
  pinMode(12,OUTPUT); 	 //forno
  pinMode(11,OUTPUT); 	 //microonde
  pinMode(10,OUTPUT); 	 //lavastoviglie
  pinMode(9,OUTPUT); 	 //frigo
  //camera da letto
  pinMode(8,OUTPUT); 	 //luce camera
  pinMode(7,OUTPUT); 	 //tv camera
  //bagno
  pinMode(6,OUTPUT); 	 //luce bagno
  pinMode(5,OUTPUT); 	 //lavatrice
  pinMode(4,OUTPUT);    //phon
  //terrazzo
  pinMode(3,OUTPUT);    //luce terrazzo
  pinMode(2,OUTPUT);    //antifurto

  Bridge.begin();
  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)

  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {
    String command = client.readStringUntil('/');

    // is "relay" command?
    //9+X = OFF -//- X = ON
    if (command == "relay") {
      int stat = client.parseInt();
      if (stat == 16) {
        digitalWrite(A2, HIGH);
        relay.on();      
      } 
      if (stat == 916) {
        digitalWrite(A2, LOW);
        relay.off();
      }
      
      if (stat == 15) {
        digitalWrite(A1, HIGH);
        relay.on();      
      } 
      if (stat == 915) {
        digitalWrite(A1, LOW);
        relay.off();
      }
      
      if (stat == 14) {
        digitalWrite(A0, HIGH);
        relay.on();      
      } 
      if (stat == 914) {
        digitalWrite(A0, LOW);
        relay.off();
      }
      
      if (stat == 13) {
        digitalWrite(13, HIGH);
        relay.on();      
      } 
      if (stat == 913) {
        digitalWrite(13, LOW);
        relay.off();
      }
      if (stat == 12) {
        digitalWrite(12, HIGH);
        relay.on();      
      } 
      if (stat == 912) {
        digitalWrite(12, LOW);
        relay.off();
      }
      if (stat == 11) {
        digitalWrite(11, HIGH);
        relay.on();      
      } 
      if (stat == 911) {
        digitalWrite(11, LOW);
        relay.off();
      }
      
     if (stat == 10) {
        digitalWrite(10, HIGH);
        relay.on();      
      } 
      if (stat == 910) {
        digitalWrite(10, LOW);
        relay.off();
      }
      
      if (stat == 9) {
        digitalWrite(9, HIGH);
        relay.on();      
      } 
      if (stat == 99) {
        digitalWrite(9, LOW);
        relay.off();
      }
      
      if (stat == 8) {
        digitalWrite(8, HIGH);
        relay.on();      
      } 
      if (stat == 98) {
        digitalWrite(8, LOW);
        relay.off();
      }
      
      if (stat == 7) {
        digitalWrite(7, HIGH);
        relay.on();      
      } 
      if (stat == 97) {
        digitalWrite(7, LOW);
        relay.off();
      }
      if (stat == 6) {
        digitalWrite(6, HIGH);
        relay.on();      
      } 
      if (stat == 96) {
        digitalWrite(6, LOW);
        relay.off();
      }
      if (stat == 5) {
        digitalWrite(5, HIGH);
        relay.on();      
      } 
      if (stat == 95) {
        digitalWrite(5, LOW);
        relay.off();
      }
      
      if (stat == 4) {
        digitalWrite(4, HIGH);
        relay.on();      
      } 
      if (stat == 94) {
        digitalWrite(4, LOW);
        relay.off();
      }
      
      if (stat == 3) {
        digitalWrite(3, HIGH);
        relay.on();      
      } 
      if (stat == 93) {
        digitalWrite(3, LOW);
        relay.off();
      }
      if (stat == 2) {
        digitalWrite(2, HIGH);
        relay.on();      
      } 
      if (stat == 92) {
        digitalWrite(2, LOW);
        relay.off();
      }    
    }



    // Close connection and free resources.

    client.stop();

  }



  delay(50); // Poll every 50ms

}
