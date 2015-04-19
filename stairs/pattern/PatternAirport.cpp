#include <limits.h>
#include "PatternAirport.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternAirport::PatternAirport(int anchorSpacing, int anchorPassiveColor, int anchorActiveColor,
  unsigned int anchorActiveDuration, unsigned int anchorPassiveDuration,
  int anchorNearColor, int wayColor, unsigned long interDelay) :
    _anchorSpacing(anchorSpacing), _anchorPassiveColor(anchorPassiveColor),
    _anchorActiveColor(anchorActiveColor), _anchorActiveDuration(anchorActiveDuration),
    _anchorPassiveDuration(anchorPassiveDuration), _anchorNearColor(anchorNearColor),
    _wayColor(wayColor), _interDelay(interDelay)
{
}

void PatternAirport::_animate()
{
    int phase = 1;
    int humanPositionOffset = 0;
    bool anchorActive = true;
    unsigned long anchorLastSwitchTime = 0;
    while (1)
    {
      float humanPosition = (this->elapsed() / 1000.0 * _humanWalkingSpeed) - humanPositionOffset;
      float humanPositionLed = humanPosition * _ledsPerMeter;

      // possibly switch anchor status
      if ( (anchorActive && anchorLastSwitchTime > _anchorActiveDuration) ||
           (!anchorActive && anchorLastSwitchTime > _anchorPassiveDuration))
      {
        anchorActive = !anchorActive;
        anchorLastSwitchTime = this->elapsed();
      }
      
      for (int i = 0; i < NBLEDS; i++)
      {
        int color;
        // first, normal way
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
        // second, handle anchors
        if (i % _anchorSpacing == 0)
        {
          // this is an anchor, active or passive ?
          color = anchorActive ? _anchorActiveColor : _anchorPassiveColor;
          // also set -1 and +1 pixels (if not out of bounds)
          if (i - 1 >= 0)
          {
            leds.setPixel(LEDS_OFFSET + i - 1, _anchorNearColor);
          }
          if (i + 1 < NBLEDS)
          {
            leds.setPixel(LEDS_OFFSET + i + 1, _anchorNearColor);
          }
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

