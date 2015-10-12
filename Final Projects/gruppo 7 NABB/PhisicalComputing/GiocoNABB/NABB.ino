#include "FastLED.h"
#define NUM_LEDS 8
#define DATA_PIN 12


int flag = 1, i, j, num, game =1, leggo1, perdente = 0, controllo = 0, minimoTasti = 0;
int pinArray[] = {2, 3, 4, 5, 6, 7, 8, 9};
int count = 0;
int leggo;
CRGB leds[NUM_LEDS];
float punti;
int colorArray[8];
int puntiArray[8];
boolean tastiArray[8];
boolean tastigiustiArray[8];

long randomnumber;


void setup()
{
  Serial.begin(9600);

  for (count = 0; count < 8; count++) {
    pinMode(pinArray[count], INPUT_PULLUP);
  }
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  

  randomSeed(analogRead(A0));

  for (int i = 0; i < 8; i++)
  {
    tastiArray[i] = false;
    colorArray[i] = random(1, 3);
    if (colorArray[i] == 2)
    {
      tastigiustiArray[i] = true;
      minimoTasti++;
    }
    else
    {
      tastigiustiArray[i] = false;
    }
    if (i == 7 && minimoTasti < 1)
    {
      i = 0;
    }

  }

}
void loop()
{


  //solo modalità da 8 giocatori
  
  



  for (i = 0; i < 8; i++)
  {
    if (colorArray[i] == 1)
    {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    if (colorArray[i] == 2)
    {
      leds[i] = CRGB::Green;
      FastLED.show();
    }
    if (colorArray[i] == 3)
    {
      leds[i] = CRGB::Blue;
      FastLED.show();
    }
    if (colorArray[i] == 4)
    {
      leds[i] = CRGB::Yellow;
      FastLED.show();
    }
    if (colorArray[i] == 5)
    {
      leds[i] = CRGB::Pink;
      FastLED.show();
    }
    if (colorArray[i] == 6)
    {
      leds[i] = CRGB::Purple;
      FastLED.show();
    }
  }

  if ( game == 1 )
  {

    for (i = 0; i < 8; i++)
    {
      leggo = digitalRead(pinArray[i]);


      if (leggo == LOW)
      {
        tastiArray[i] = true;
        Serial.print(pinArray[i]);
        Serial.print(" - ");
        Serial.println("acceso");

        if (tastigiustiArray[i] == true)
        {
          perdente = i;
        }
        if (tastigiustiArray[i] == false)
        {
          game = 10;
          perdente = i;
          colorArray[perdente] = 3;

          Serial.println(colorArray[perdente]);

          i = 10;
        }
      }
    }

    for (j = 0; j < 8; j++)
    {
      if (tastiArray[j] == tastigiustiArray[j])
      {
        controllo++;//controllo che gli array siano uguli tra loro in tal caso il gioco finisce
      }
    }
    if (controllo == 8)
    {
      game = 10;
      colorArray[perdente] = 3;

    }
    else
    {
      controllo = 0;
    }
  }

  //////////////////////////////////////////
  if (game == 10)
  {
    leggo = digitalRead(pinArray[0]);
    leggo1 = digitalRead(pinArray[7]);
    if(leggo == LOW && leggo1 == LOW)
  {
      for (int i = 0; i < 8; i++)
      {
        tastiArray[i] = false;
        colorArray[i] = random(1, 3);
        if (colorArray[i] == 2)
        {
          tastigiustiArray[i] = true;
          minimoTasti++;

        }
        else
        {
          tastigiustiArray[i] = false;
        }
        if (i == 7 && minimoTasti < 1)
        {
          i = 0;
        }
    
      game = 1;
      
      delay(2000);
    }
  }
  }

}


