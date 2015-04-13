#include "pattern_worms.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

void pattern_worms(int nbWorms, int wormsSections[], int wormsLength, int maxSlowness)
{
  // init stuff
  int wormsDirection[nbWorms];
  int wormsSpeed[nbWorms];
  int wormsHue[nbWorms];
  int wormsSleep[nbWorms];
//  int wormsLength = sizeof(wormsSections) / sizeof(wormsSections[0]);
  int wormsBody[nbWorms * wormsLength];
  
  for (int w = 0; w < nbWorms; w++)
  {
    for (int i = 0; i < wormsLength; i++)
    {
        wormsBody[w*wormsLength + i] = i;
    }
    wormsDirection[w] = 1;
    wormsSpeed[w] = random(0,maxSlowness);
    wormsHue[w]   = random(0,360);
    wormsSleep[w] = 0;
  }

  // main loop  
  int steps = 1000;
  while (steps-- > 0)
  {
    digitalWrite(13, HIGH);

    // clear the leds
    for (int i = 0; i < NBLEDS; i++)
    {
      leds.setPixel(LEDS_OFFSET + i, 0);
    }

    // for each worm ...
    for (int w = 0; w < nbWorms; w++)
    {
      // does this worm need to move ?
      if (wormsSleep[w]++ > wormsSpeed[w])
      {
        // yep i need to move ! first, reset my counter..;
        wormsSleep[w] = 0;
      
        // if we're at top or bottom, do some funny stuff
        int headPosition = wormsBody[w*wormsLength + wormsLength-1];
        if (headPosition >= NBLEDS - 1 || headPosition <= 0)
        {
          wormsDirection[w] *= -1; // change direction
          wormsSpeed[w] = random(0,maxSlowness); // change speed
          wormsHue[w] = random(0,360); // change color
        }
        // TODO: collision
  
        // advance the tail
        for (int i = 0; i < wormsLength - 1; i++)
        {
          wormsBody[w*wormsLength + i] = wormsBody[w*wormsLength + i+1];
        }
        // and set the head
        wormsBody[w*wormsLength + wormsLength-1] += wormsDirection[w];
      }
      
      // set the colors now, from tail to head
      // because the head must always have the last word
      for (int i = 0; i < wormsLength; i++)
      {
        leds.setPixel(LEDS_OFFSET + wormsBody[w*wormsLength + i], makeColor(wormsHue[w], 100, wormsSections[i]));
      }
    }
    
    leds.show();
    digitalWrite(13, LOW);
//    delayMicroseconds(1000*3);
  }
}


