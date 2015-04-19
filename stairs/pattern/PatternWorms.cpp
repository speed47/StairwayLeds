#include <limits.h>
#include "PatternWorms.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternWorms::PatternWorms(int nbWorms, int *worm, int wormLen, int maxSlowness) :
  nbWorms(nbWorms), worm(worm), wormLen(wormLen), maxSlowness(maxSlowness)
{
}

void PatternWorms::_animate()
{
  // init stuff
  int wormsDirection[nbWorms];
  int wormsSpeed[nbWorms];
  int wormsHue[nbWorms];
  int wormsSleep[nbWorms];
  int wormsBody[nbWorms * wormLen];
  
  for (int w = 0; w < nbWorms; w++)
  {
    int firstLed = random(0, NBLEDS - wormLen);
    for (int i = 0; i < wormLen; i++)
    {
        wormsBody[w*wormLen + i] = i + firstLed;
    }
    wormsDirection[w] = 1;
    wormsSpeed[w] = random(0,maxSlowness);
    wormsHue[w]   = random(0,360);
    wormsSleep[w] = 0;
  }

  // main loop  
  int steps = 2000;
  while (steps-- > 0)
  {
    digitalWrite(TEENSY_LED_PIN, HIGH);

    // clear the leds
    ledsClear();

    // for each worm ...
    for (int w = 0; w < nbWorms; w++)
    {
      // does this worm need to move ?
      if (wormsSleep[w]++ > wormsSpeed[w])
      {
        // yep i need to move ! first, reset my counter..;
        wormsSleep[w] = 0;
      
        // if we're at top or bottom, do some funny stuff
        int headPosition = wormsBody[w*wormLen + wormLen-1];
        if (headPosition >= NBLEDS - 1 || headPosition <= 0)
        {
          wormsDirection[w] *= -1; // change direction
          wormsSpeed[w] = random(0,maxSlowness); // change speed
          wormsHue[w] = random(0,360); // change color
        }
        // TODO: collision
  
        // advance the tail
        for (int i = 0; i < wormLen - 1; i++)
        {
          wormsBody[w*wormLen + i] = wormsBody[w*wormLen + i+1];
        }
        // and set the head
        wormsBody[w*wormLen + wormLen-1] += wormsDirection[w];
      }
      
      // set the colors now, from tail to head
      // because the head must always have the last word
      for (int i = 0; i < wormLen; i++)
      {
        leds.setPixel(LEDS_OFFSET + wormsBody[w*wormLen + i], makeColor(wormsHue[w], 100, worm[i]));
      }
    }
    
    leds.show();
    digitalWrite(TEENSY_LED_PIN, LOW);
//    delay(3);
  }
}


