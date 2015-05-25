#include <limits.h>
#include "PatternWorms.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternWorms::PatternWorms(int nbWorms, int *worm, int wormLen, int lowerSpeed, unsigned int duration) :
  _nbWorms(nbWorms), _worm(worm), _wormLen(wormLen), _lowerSpeed(lowerSpeed), _duration(duration)
{
}

void PatternWorms::_animate(direction_t direction)
{
  // init stuff
  int wormsDirection[_nbWorms];
  int wormsSpeed[_nbWorms];
  int wormsHue[_nbWorms];
  int wormsSleep[_nbWorms];
  int wormsBody[_nbWorms * _wormLen];
  
  for (int w = 0; w < _nbWorms; w++)
  {
    int firstLed = random(0, NBLEDS - _wormLen);
    int direction = (random(0, 2) == 0 ? -1 : 1);
    for (int i = 0; i < _wormLen; i++)
    {
        wormsBody[w*_wormLen + i] = firstLed + (i * direction);
    }
    wormsDirection[w] = direction;
    wormsSpeed[w] = random(0,_lowerSpeed);
    wormsHue[w]   = random(0,360);
    wormsSleep[w] = 0;
  }

  // main loop  
  while (this->elapsed() < _duration)
  {
    ++this->_iterations;

    // clear the leds
    ledsClear();

    // for each worm ...
    for (int w = 0; w < _nbWorms; w++)
    {
      // does this worm need to move ?
      if (wormsSleep[w]++ > wormsSpeed[w])
      {
        // yep i need to move ! first, reset my counter..;
        wormsSleep[w] = 0;
      
        // if we're at top or bottom, do some funny stuff
        int headPosition = wormsBody[w*_wormLen + _wormLen-1];
        if (headPosition >= NBLEDS - 1 || headPosition <= 0)
        {
          wormsDirection[w] *= -1; // change direction
          //wormsSpeed[w] = random(0,_lowerSpeed); // change speed
          //wormsHue[w] = random(0,360); // change color
        }
        // TODO: collision
  
        // advance the tail
        for (int i = 0; i < _wormLen - 1; i++)
        {
          wormsBody[w*_wormLen + i] = wormsBody[w*_wormLen + i+1];
        }
        // and set the head
        wormsBody[w*_wormLen + _wormLen-1] += wormsDirection[w];
      }
      
      // set the colors now, from tail to head
      // because the head must always have the last word
      for (int i = 0; i < _wormLen; i++)
      {
        setPix(direction, LEDS_OFFSET, wormsBody[w*_wormLen + i], makeColor(wormsHue[w], 100, _worm[i]));
      }
    }
    
    leds.show();
  }
}


