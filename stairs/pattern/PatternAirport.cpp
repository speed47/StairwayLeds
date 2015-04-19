#include <limits.h>
#include "PatternAirport.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternAirport::PatternAirport(int anchorSpacing = 20, int anchorColorPassive = 0x1F1F1F, int anchorColorActive = 0xFFFFFF,
  int anchorNearColor = 0x20CC20, int wayColor = 0x400000, unsigned long interDelay = 2000) :
    _anchorSpacing(anchorSpacing), _anchorColorPassive(anchorColorPassive),
    _anchorColorActive(anchorColorActive), _anchorNearColor(anchorNearColor),
    _wayColor(wayColor), _interDelay(interDelay)
{
}

void PatternAirport::_animate()
{
    int phase = 1;
    int humanPositionOffset = 0;
    while (!(phase == 2 && humanPositionLed > NBLEDS))
    {
      float humanPosition = (this->elapsed() / 1000.0 * _humanWalkingSpeed) - humanPositionOffset;
      float humanPositionLed = humanPosition * _ledsPerMeter;
      
      for (int i = 0; i < NBLEDS; i++)
      {
        int luminosity;
        if (phase == 1)
        {
          if      (humanPositionLed <  i    ) { luminosity = 0; }
          else if (humanPositionLed >= i + 1) { luminosity = mainLuminosity; }
          else
          {
            luminosity = mainLuminosity * (humanPositionLed - (int)humanPositionLed);
            dbg3("phase=%d humanPositionLed=%.1f led.%d=%d", phase, humanPositionLed, i, luminosity);
          }
        }
        else
        {
          if      (humanPositionLed >  i    ) { luminosity = 0; }
          else if (humanPositionLed <= i - 1) { luminosity = mainLuminosity; }
          else
          {
            luminosity = mainLuminosity * (1 - (humanPositionLed - (int)humanPositionLed));
            dbg3("phase=%d humanPositionLed=%.1f led.%d=%d", phase, humanPositionLed, i, luminosity);
          }
        }
        leds.setPixel(LEDS_OFFSET + i, makeColor(this->mainHue->value, 100, luminosity));
      }
      
      leds.show();

      if (phase == 1 && humanPositionLed > NBLEDS)
      {
        phase = 2;
        humanPositionOffset = NBLEDS * _ledsPerMeter;
      }
    }
}

