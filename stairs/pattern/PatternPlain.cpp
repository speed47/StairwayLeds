#include <limits.h>
#include "PatternPlain.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternPlain::PatternPlain(int color, unsigned int duration) : _color(color), _duration(duration)
{
}

void PatternPlain::_animate(direction_t direction)
{
  for (int i = 0; i < NBLEDS; i++)
  {
    setPix(direction, LEDS_OFFSET, i, _color);
  }
  ++this->_iterations;
  leds.show();
  digitalWrite(TEENSY_LED_PIN, LOW);
  delay(_duration);
}
  
