#include <limits.h>
#include "PatternPlain.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternPlain::PatternPlain(int color, unsigned int duration) : _color(color), _duration(duration)
{
}

void PatternPlain::_animate()
{
  while (this->elapsed() < _duration)
  {
    for (int i = 0; i < NBLEDS; i++)
    {
      leds.setPixel(LEDS_OFFSET + i, _color);
    }
    leds.show();
  }
}
  
