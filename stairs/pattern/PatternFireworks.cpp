#include <limits.h>
#include "PatternFireworks.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternFireworks::PatternFireworks(int probability, unsigned int delay, unsigned long duration) :
  _probability(probability), _delay(delay), _duration(duration)
{
  if (probability < 1)
  {
    dbg1("PatternFireworks ctor: adjusting given probability (%d) to 1", probability);
    _probability = 1;
  }
}

void PatternFireworks::_animate()
{
  while (this->elapsed() < this->_duration)
  {
    ++this->_iterations;
    digitalWrite(TEENSY_LED_PIN, HIGH);
    for (int led = 0; led < NBLEDS; led++)
    {
      int color = 0;
      if (random(0, this->_probability) >= this->_probability - 1)
      {
        color = makeColor(random(0,361), 100, random(1,51));
      }
      leds.setPixel(LEDS_OFFSET + led, color);
    }
    leds.show();
    digitalWrite(TEENSY_LED_PIN, LOW);
    delay(this->_delay);
  }
}

