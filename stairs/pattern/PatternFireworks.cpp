#include <limits.h>
#include "PatternFireworks.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"
#include "helpers.h"

PatternFireworks::PatternFireworks(unsigned int delay, unsigned long duration, float dimSpeed) :
  _delay(delay), _duration(duration), _dimSpeed(dimSpeed)
{
}

void PatternFireworks::_animate(direction_t direction)
{
  int8_t ledsLum[NBLEDS]  = {0};
  int8_t ledsHue[NBLEDS]  = {0};
  unsigned long lastLoop = 0;
  unsigned long lastLit  = 0;
  while (this->elapsed() < this->_duration)
  {
    ++this->_iterations;
    digitalWrite(TEENSY_LED_PIN, HIGH);
    int nbLedsToLit = (this->elapsed() - lastLit) / _delay;
    if (nbLedsToLit > 0)
    {
      lastLit = this->elapsed();
    }
    dbg3("wanna lit %d leds, lastLit=%lu elapsed=%lu", nbLedsToLit, lastLit, this->elapsed());
    for (int led = 0; led < nbLedsToLit; led++)
    {
      // randomly lit a number of <led> leds
      int i = findOneRandomPoweredLed(direction, POWERED_OFF, LEDS_OFFSET, 0, NBLEDS);
      if (i >= 0)
      {
        ledsLum[i] = random(0, 51);
        ledsHue[i] = random(0, 360);
        setPix(direction, LEDS_OFFSET, i, makeColor(ledsHue[i], 100, ledsLum[i]));
        dbg3("powered on led %d at lum %d", i, ledsLum[i]);
      }
    }
    // now slowly dim off all leds
    unsigned int elapsedLoop = this->elapsed() - lastLoop;
    lastLoop = this->elapsed();
    for (int i = 0; i < NBLEDS; i++)
    {
      if (getPix(direction, LEDS_OFFSET, i) != 0x000000)
      {
        dbg3("dimming led %d to %d", i, ledsLum[i]);
        ledsLum[i] -= this->_dimSpeed * elapsedLoop;
        if (ledsLum[i] < 0) { ledsLum[i] = 0; }
        setPix(direction, LEDS_OFFSET, i, makeColor(ledsHue[i], 100, ledsLum[i]));
      }
    }
    leds.show();
    digitalWrite(TEENSY_LED_PIN, LOW);
  }
}


