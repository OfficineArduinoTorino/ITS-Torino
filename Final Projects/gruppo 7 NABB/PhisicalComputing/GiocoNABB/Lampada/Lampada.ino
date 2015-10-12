#include "FastLED.h"
#define NUM_LEDS 8
#define DATA_PIN 12
int i;
int colorArray[8];
CRGB leds[NUM_LEDS];
void setup() {

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  randomSeed(analogRead(A0));
  for (int i = 0; i < 8; i++)
  {
    colorArray[i] = random(1, 7);
  }
}

void loop()
{
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
  for (int i = 0; i < 8; i++)
    {
      
      colorArray[i] = random(1, 7);
    }
    delay(3000);

}
