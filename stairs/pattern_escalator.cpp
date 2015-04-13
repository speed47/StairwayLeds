#include "pattern_escalator.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

void pattern_escalator(void)
{
    const int mainLuminosity = 30;
    const int glowLuminosity = 50;
    const float glowSpeed = 1.5;
    const int glowOften = 1;
    
    int glowHue;
    int mainHue = random(0,360);
    int triggerGlow = glowOften;
    float flowPosition = 0;
    boolean glowing = false;
    
    unsigned long animationStart = millis();
    int phase = 1;
    while (1)
    {
      // in case of overflow
      if (millis() < animationStart) { animationStart = 0; }

      unsigned long elapsedTime = millis() - animationStart;
      float humanPosition = elapsedTime / 1000.0 * humanWalkingSpeed;
      float humanPositionLed = humanPosition * ledsPerMeter;
      
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
          else if (humanPositionLed <= i + 1) { luminosity = mainLuminosity; }
          else
          {
            luminosity = mainLuminosity * (humanPositionLed - (int)humanPositionLed);
            dbg3("phase=%d humanPositionLed=%.1f led.%d=%d", phase, humanPositionLed, i, luminosity);
          }
        }
        leds.setPixel(LEDS_OFFSET + i, makeColor(mainHue, 100, luminosity));
      }
      
      if (!glowing && triggerGlow-- < 0)
      {
        glowing = true;
        flowPosition = NBLEDS;
        glowHue = random(0,360);
      }
      
      if (glowing && flowPosition < 0)
      {
        glowing = false;
        triggerGlow = glowOften;
      }
      
      if (glowing)
      {
        flowPosition -= glowSpeed;
        leds.setPixel(LEDS_OFFSET +  (int)flowPosition, makeColor(glowHue, 100, glowLuminosity));
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
    }
}

