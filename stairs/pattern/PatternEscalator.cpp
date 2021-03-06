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

void PatternEscalator::_animate(direction_t direction)
{
    int glowHue;
    int triggerGlow = glowOften;
    float flowPosition = 0;
    boolean glowing = false;
    
    int phase = 1;
    float humanPositionOffset = 0;

    this->mainHue->randomize();

    while (1)
    {
      ++this->_iterations;
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
        setPix(direction, LEDS_OFFSET, i, makeColor(this->mainHue->value, 100, luminosity));
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
        setPix(direction, LEDS_OFFSET,  (int)flowPosition, makeColor(glowHue, 100, glowLuminosity));
      }
      
      leds.show();

      if (phase == 1 && humanPositionLed > NBLEDS)
      {
        phase = 2;
        humanPositionOffset = (NBLEDS / (float)_ledsPerMeter);
      }

      else if (phase == 2 && humanPositionLed > NBLEDS)
      {
        break;
      }
    }
}

