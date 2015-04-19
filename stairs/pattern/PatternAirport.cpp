#include <limits.h>
#include "PatternAirport.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternAirport::PatternAirport(int anchorSpacing, int anchorColorPassive, int anchorColorActive,
  int anchorNearColor, int wayColor, unsigned long interDelay) :
    _anchorSpacing(anchorSpacing), _anchorColorPassive(anchorColorPassive),
    _anchorColorActive(anchorColorActive), _anchorNearColor(anchorNearColor),
    _wayColor(wayColor), _interDelay(interDelay)
{
}

void PatternAirport::_animate()
{
    int phase = 1;
    int humanPositionOffset = 0;
    while (1)
    {
      float humanPosition = (this->elapsed() / 1000.0 * _humanWalkingSpeed) - humanPositionOffset;
      float humanPositionLed = humanPosition * _ledsPerMeter;
      
      for (int i = 0; i < NBLEDS; i++)
      {
        int color;
        if (phase == 1)
        {
          if      (humanPositionLed <= i    ) { color = 0; }
          else if (humanPositionLed >= i + 1) { color = _wayColor; }
        }
        else
        {
          if      (humanPositionLed >= i    ) { color = 0; }
          else if (humanPositionLed <= i - 1) { color = _wayColor; }
        }
        leds.setPixel(LEDS_OFFSET + i, color);
      }
      
      leds.show();

      if (phase == 1 && humanPositionLed > NBLEDS)
      {
        phase = 2;
        humanPositionOffset = NBLEDS * _ledsPerMeter;
      }

      if (phase == 2 && humanPositionLed > NBLEDS)
      {
        break;
      }
    }
}

