#include <limits.h>
#include "PatternK2000.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternK2000::PatternK2000(int baseHue, int* aLight, int aLightLen) :
  baseHue(baseHue), aLight(aLight), aLightLen(aLightLen)
{
}

void PatternK2000::_animate()
{
  int currentDirection = 1;
  int length = aLightLen;
  int k[length];

  // setup the head and tail  
  for (int i = 0; i < length; i++)
  {
    k[i] = i;
  }
  // start clean with black leds
  /*
  for (int led = 0; led < NBLEDS; led++)
   {
    leds.setPixel(LEDS_OFFSET + led, 0); // all leds are black by default
  }*/
  
  int steps = 1000;
  while (steps-- > 0)
  {
    baseHue = baseHue + 3 % 360;
    digitalWrite(13, HIGH);
    // reverse direction if we're at the top
    if (k[length-1] >= NBLEDS - 1)
    {
      currentDirection = -1; // down
    }
    // reverse direction if we're at the bottom
    else if (k[length-1] <= 0)
    {
      currentDirection = 1; // up
    }
    
    // before advancing the tail, power off the last tail led
    // the others are either already black or will still be part
    // of the lighted leds of this step
    leds.setPixel(LEDS_OFFSET + k[0], 0);
    
    // advance the tail
    for (int i = 0; i < length - 1; i++)
    {
      k[i] = k[i+1];
    }
    // and set the head
    k[length-1] += currentDirection;
    
    // set the colors now, from tail to head
    // because the head must always have the last word
    for (int i = 0; i < length; i++)
    {
      leds.setPixel(LEDS_OFFSET + k[i], makeColor(baseHue, 100, aLight[i]));
    }
    
    // now display
    leds.show();
    digitalWrite(13, LOW);
    delayMicroseconds(1000*5);
  }
}
  
