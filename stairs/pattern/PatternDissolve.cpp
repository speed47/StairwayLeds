#include <limits.h>
#include "PatternDissolve.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"
#include "helpers.h"

PatternDissolve::PatternDissolve(unsigned int delay, unsigned int delayBetweenPhases, Randomizer* colorPicker, Randomizer* luminosityPicker) :
  _delay(delay), _delayBetweenPhases(delayBetweenPhases), _colorPicker(colorPicker), _luminosityPicker(luminosityPicker)
{
}

PatternDissolve::~PatternDissolve()
{
  delete this->_colorPicker;
  delete this->_luminosityPicker;
}

void PatternDissolve::_animate()
{
  int phase = 1;
  while (1)
  {
    digitalWrite(TEENSY_LED_PIN, HIGH);
    ++this->_iterations;
    // choose a led to lit
    int ledCandidate = findOneRandomPoweredLed(leds, phase == 1 ? POWERED_OFF : POWERED_ON, LEDS_OFFSET, 0, NBLEDS);
    if (ledCandidate < 0)
    {
      // at the other extremity now ?? ok, so actually everybody is lit (or off). STOOOOOP
      digitalWrite(TEENSY_LED_PIN, LOW);
      if (phase == 1)
      {
        delay(this->_delayBetweenPhases);
        phase = 2;
        continue;
      }
      else if (phase == 2)
      {
        digitalWrite(TEENSY_LED_PIN, HIGH);
        break;
      }
    }
    // ok, let's power on (or off) ledCandidate
    if (phase == 1)
    {
      this->_colorPicker->randomize();
      this->_luminosityPicker->randomize();
      leds.setPixel(LEDS_OFFSET + ledCandidate, makeColor(this->_colorPicker->value, 100, this->_luminosityPicker->value));
    }
    else
    {
      leds.setPixel(LEDS_OFFSET + ledCandidate, 0x000000);
    }
    leds.show();
    digitalWrite(TEENSY_LED_PIN, LOW);
    delay(this->_delay);
  }
}

