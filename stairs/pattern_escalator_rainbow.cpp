#include "pattern_escalator.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

void pattern_escalator_rainbow(void)
{
    const int mainLuminosity = 40;
    const int delayFirst = 1000 * 30;
    const int delayLast  = 1000 / 10;

    unsigned long animationStart = millis();
    int phase = 1;
    int shift = random(0,180);
    int delay = delayFirst;
    int delayStepPerLed = (delayFirst - delayLast) / (float)(NBLEDS * 2);
    while (1)
    {
      // in case of overflow
      if (millis() < animationStart) { animationStart = 0; }

      unsigned long elapsedTime = millis() - animationStart;
      float humanPosition = elapsedTime / 1000.0 * humanWalkingSpeed;
      float humanPositionLed = humanPosition * ledsPerMeter;
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
          else if (humanPositionLed <= i + 1) { luminosity = mainLuminosity; }
          else
          {
            luminosity = mainLuminosity * (humanPositionLed - (int)humanPositionLed);
            dbg3("phase=%d humanPos=%.1f humanPosLedTot=%.1f humanPosLed=%.1f delay=%d led.%d=%d", phase, humanPosition, humanPositionLedTotal, humanPositionLed, delay, i, luminosity);
          }
        }
        leds.setPixel(LEDS_OFFSET + i, makeColor( (hue * 7) % 180, 100, luminosity));
      }
      
      leds.show();

      if (phase == 1 && humanPositionLed > NBLEDS)
      {
        phase = 2;
        animationStart = millis();
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

