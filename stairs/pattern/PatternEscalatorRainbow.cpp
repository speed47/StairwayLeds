#include <limits.h>
#include "PatternEscalatorRainbow.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternEscalatorRainbow::PatternEscalatorRainbow(int mainLuminosity, int delayFirst, int delayLast, int hueMultiplier, float delayBetweenPhases) :
  mainLuminosity(mainLuminosity), delayFirst(delayFirst), delayLast(delayLast), hueMultiplier(hueMultiplier), delayBetweenPhases(delayBetweenPhases)
{
}

PatternEscalatorRainbow::~PatternEscalatorRainbow()
{
}


void PatternEscalatorRainbow::_animate()
{
    int phase = 1;
    int humanPositionOffset = 0;
    int shift = random(0,180);
    int delay = delayFirst;
    int delayStepPerLed = (delayFirst - delayLast) / (float)(NBLEDS * 2);
    while (1)
    {
      float humanPosition = (this->elapsed() / 1000.0 * _humanWalkingSpeed) - humanPositionOffset;;
      float humanPositionLed = humanPosition * _ledsPerMeter;
      float humanPositionLedTotal = humanPositionLed + ((phase - 1) * NBLEDS);
      delay = delayFirst - (int)(delayStepPerLed * humanPositionLedTotal);
      if (delay < 0 || delay > 1000*1000)
      {
        delay = 0;
      }

      shift++;
      
      for (int i = 0; i < NBLEDS; i++)
      {
        int luminosity;
        int hue = (shift + i) % 180;
        if (phase == 1)
        {
          if      (humanPositionLed <  i    ) { luminosity = 0; }
          else if (humanPositionLed >= i + 1) { luminosity = mainLuminosity; }
          else
          {
            luminosity = mainLuminosity * (humanPositionLed - (int)humanPositionLed);
            dbg3("phase=%d humanPos=%.1f humanPosLedTot=%.1f humanPosLed=%.1f delay=%d led.%d=%d", phase, humanPosition, humanPositionLedTotal, humanPositionLed, delay, i, luminosity);
          }
        }
        else
        {
          if      (humanPositionLed >  i    ) { luminosity = 0; }
          else if (humanPositionLed <= i - 1) { luminosity = mainLuminosity; }
          else
          {
            luminosity = mainLuminosity * (1 - (humanPositionLed - (int)humanPositionLed));
            dbg3("phase=%d humanPos=%.1f humanPosLedTot=%.1f humanPosLed=%.1f delay=%d led.%d=%d", phase, humanPosition, humanPositionLedTotal, humanPositionLed, delay, i, luminosity);
          }
        }
        leds.setPixel(LEDS_OFFSET + i, makeColor( (hue * hueMultiplier) % 180, 100, luminosity));
      }
      
      leds.show();

      if (phase == 1 && humanPositionLed > NBLEDS)
      {
        phase = 2;
        humanPositionOffset = NBLEDS * _ledsPerMeter;
      }
      
      else if (phase == 2 && humanPositionLed > NBLEDS)
      {
        for (int i = 0; i < NBLEDS; i++)
        {
          leds.setPixel(LEDS_OFFSET + i, 0);
        }
        leds.show();
        break;
      }

    delayMicroseconds(delay);
    }
}

