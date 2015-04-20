#include <limits.h>
#include "PatternAirport.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternAirport::PatternAirport(int anchorSpacing, int anchorPassiveColor, int anchorActiveColor,
  unsigned int anchorActiveDuration, unsigned int anchorPassiveDuration,
  int anchorNearColor, int wayColor, unsigned long delayBetweenPhases) :
    _anchorSpacing(anchorSpacing), _anchorPassiveColor(anchorPassiveColor),
    _anchorActiveColor(anchorActiveColor), _anchorActiveDuration(anchorActiveDuration),
    _anchorPassiveDuration(anchorPassiveDuration), _anchorNearColor(anchorNearColor),
    _wayColor(wayColor), _delayBetweenPhases(delayBetweenPhases)
{
}

void PatternAirport::_animate()
{
    int phase = 1;
    float humanPositionOffset = 0;
    bool anchorActive = true;
    unsigned long anchorLastSwitchTime = 0;
    unsigned long lastPhaseChange = 0;
    while (1)
    {
      ++this->_iterations;
      float humanPosition = (this->elapsed() / 1000.0 * _humanWalkingSpeed) - humanPositionOffset;
      float humanPositionLed = humanPosition * _ledsPerMeter;
      unsigned long anchorLastSwitchDiff = this->elapsed() - anchorLastSwitchTime;

      dbg3("phase=%d humanPos=%.1f humanPosLed=%d anchorActive=%d, anchorLastSwitchDiff=%lu", phase, humanPosition, (int)humanPositionLed, anchorActive, anchorLastSwitchDiff);
      // possibly switch anchor status
      if ( (anchorActive && anchorLastSwitchDiff > _anchorActiveDuration) ||
           (!anchorActive && anchorLastSwitchDiff > _anchorPassiveDuration))
      {
        anchorActive = !anchorActive;
        anchorLastSwitchTime = this->elapsed();
      }
      
      // first, normal way
      for (int i = 0; i < NBLEDS; i++)
      {
        int color = 0;
        if (phase == 1)
        {
          if (humanPositionLed >= i + 1) { color = _wayColor; }
        }
        else if (phase == 2)
        {
          color = _wayColor;
        }
        else if (phase == 3)
        {
          if (humanPositionLed <= i - 1) { color = _wayColor; }
        }
        leds.setPixel(LEDS_OFFSET + i, color);
      }
      // second, handle anchors
      for (int i = _anchorSpacing / 2; i < NBLEDS; i += _anchorSpacing)
      {
        // this is an anchor, active or passive ?
        leds.setPixel(LEDS_OFFSET + i, anchorActive ? _anchorActiveColor : _anchorPassiveColor);
        // when passive, also sometimes
        // set -1 and +1 pixels (if not out of bounds)
        if (!anchorActive)
        {
          if (anchorLastSwitchDiff >= 100 && anchorLastSwitchDiff < 200 && i - 1 >= 0)
          {
            leds.setPixel(LEDS_OFFSET + i - 1, _anchorNearColor);
          }
          if (anchorLastSwitchDiff >= 200 && anchorLastSwitchDiff < 300 && i + 1 < NBLEDS)
          {
            leds.setPixel(LEDS_OFFSET + i + 1, _anchorNearColor);
          }
        }
      }
      
      leds.show();

      if (phase == 1 && humanPositionLed > NBLEDS)
      {
        phase = 2;
        humanPositionOffset = humanPosition;
        lastPhaseChange = this->elapsed();
      }
      else if (phase == 2)
      {
        if (this->elapsed() - lastPhaseChange > _delayBetweenPhases)
        {
          phase = 3;
          humanPositionOffset += humanPosition;
        }
      }
      else if (phase == 3 && humanPositionLed > NBLEDS && !anchorActive && anchorLastSwitchDiff > 300)
      {
        break;
      }
    }
}

