#include <limits.h>
#include "PatternEscalator.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternEscalator::PatternEscalator(int mainLuminosity, int glowLuminosity, float glowSpeed, int glowOften, Randomizer *mainHue) :
  mainLuminosity(mainLuminosity), glowLuminosity(glowLuminosity), glowSpeed(glowSpeed), glowOften(glowOften), mainHue(mainHue)
{
}

PatternEscalator::~PatternEscalator()
{
  delete this->mainHue;
}

void PatternEscalator::_randomize()
{
  this->mainHue->randomize();
}

void PatternEscalator::_animate()
{
    int glowHue;
    int triggerGlow = glowOften;
    float flowPosition = 0;
    boolean glowing = false;
    
    int phase = 1;
    int humanPositionOffset = 0;
    while (1)
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
    }
}

