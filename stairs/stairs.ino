#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

#include "pattern/PatternEscalator.h"
#include "pattern/PatternEscalatorRainbow.h"
#include "pattern_worms.h"
#include "pattern_k2000.h"
#include "pattern_fireworks.h"

#include <OctoWS2811.h>

// globals of octows2811
DMAMEM int displayMemory[NBLEDS*6];
int drawingMemory[NBLEDS*6];
OctoWS2811 leds(NBLEDS, displayMemory, drawingMemory, WS2811_GRB | WS2811_800kHz);

// patterns
Pattern *patterns[] = {
  new PatternEscalator(),
  new PatternEscalatorRainbow(20,   1*1000,     1000, 2, 1.0),
  new PatternEscalatorRainbow(30,  30*1000,        1, 7, 2.0)
};

void setup()
{
  // enable %f and such
  asm(".global _printf_float");
  // pins setup
  pinMode(BOTTOM_MOTION_DETECTOR_PIN, INPUT);
  pinMode(TEENSY_LED_PIN, OUTPUT);
  // shut off the teensy led
  digitalWrite(TEENSY_LED_PIN, LOW);
  // octows2811 setup
  leds.begin();
  // done
  dbg1("setup done");
}

void loop()
{
  int motionBottom, motionTop;
  int nbpatterns = sizeof(patterns);
  while (1)
  {
    // power-on teensy led
    digitalWrite(TEENSY_LED_PIN, HIGH);
    // read detectors
    motionBottom = analogRead(BOTTOM_MOTION_DETECTOR_PIN);
    motionTop    = 0;//analogRead(   TOP_MOTION_DETECTOR_PIN);

    dbg2("motion sensor: %d", motionBottom);
    if (motionBottom < DETECTION_THRESHOLD && motionTop < DETECTION_THRESHOLD)
    {
      // no motion detected, shut everything off
      for (int i = 0; i < NBLEDS; i++)
      {
        leds.setPixel(LEDS_OFFSET + i, 0x000000);
      }
      leds.show();
    }
    else
    {
      int hue = 200; // red
      int aLightness[] = {1, 2, 4, 6, 15, 25};

      // number of worms we want, yay !
      int nbWorms = NBLEDS / 20;
      // lightness of each body part, here we have 3-led long worms
      int wormsSections[] = { 1, 5, 10, 15, 9, 5, 4, 6, 7, 30 };
      // the higher, the slower a worm can get. a number like 2 or 3 will burn your eyes
      int maxSlowness = 30;
      // motion detected
      int chosen = random(0, nbpatterns + 3);
      dbg1("MOTION DETECTED, chosen pattern: %d", chosen);
      if (chosen < nbpatterns)
      {
        patterns[chosen]->run();
      }
      else if (chosen == nbpatterns)
      {
          pattern_fireworks();
      }
      else if (chosen == nbpatterns+1)
      {
          pattern_k2000(hue, aLightness, sizeof(aLightness) / sizeof(aLightness[0]));
      }
      else if (chosen == nbpatterns+2)
      {
          pattern_worms(nbWorms, wormsSections, sizeof(wormsSections) / sizeof(wormsSections[0]), maxSlowness);
      }
    }

    // poweroff led, and wait 100ms before polling again
    digitalWrite(TEENSY_LED_PIN, LOW);
    rand(); // just to get better pseudo random numbers when we need those
    delayMicroseconds(1000 * 100);
  }
}


