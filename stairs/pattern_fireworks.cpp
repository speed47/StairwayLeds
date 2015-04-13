#include "pattern_fireworks.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

void pattern_fireworks(void)
{
  int color;

  int steps = 1000;
  while (steps-- > 0)
  {
    digitalWrite(13, HIGH);
    for (int led = 0; led < NBLEDS; led++)
    {
      color = 0;
      if (random(0,10) >= 9)
      {
        color = makeColor(rand(), 100, random(1,51));
      }
      leds.setPixel(LEDS_OFFSET + led, color);
    }
    leds.show();
    digitalWrite(13, LOW);
    delayMicroseconds(1000*15);
  }
}

