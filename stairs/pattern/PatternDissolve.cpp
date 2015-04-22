#include <limits.h>
#include "PatternDissolve.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

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
    unsigned int ledCandidate = random(0,NBLEDS);
    bool found = false;
    int direction = random(0,2) == 1 ? 1 : -1;
    // is it lit (or off) already ?
    while (ledCandidate >= 0 && ledCandidate < NBLEDS)
    {
      if (phase == 1 && leds.getPixel(LEDS_OFFSET + ledCandidate) == 0x000000)
      {
        // it's off, found ! will turn it on
        found = true;
        break;
      }
      else if (phase == 2 && leds.getPixel(LEDS_OFFSET + ledCandidate) != 0x000000)
      {
        // it's on, found ! will turn it off
        found = true;
        break;
      }
      // find the closer one in specified direction
      ledCandidate += direction;
    }
    if (!found)
    {
      // damn, we are at an extremity, go back the other way !
      ledCandidate -= direction;
      while (ledCandidate >= 0 && ledCandidate < NBLEDS)
      {
        if (phase == 1 && leds.getPixel(LEDS_OFFSET + ledCandidate) == 0x000000)
        {
          // it's off, found ! will turn it on
          found = true;
          break;
        }
        else if (phase == 2 && leds.getPixel(LEDS_OFFSET + ledCandidate) != 0x000000)
        {
          // it's on, found ! will turn it off
          found = true;
          break;
        }
        // find the closed one in specified reverse direction
        ledCandidate -= direction;
      }
    }
    if (!found)
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

