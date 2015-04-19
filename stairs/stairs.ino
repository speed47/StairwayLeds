#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

#include "pattern/PatternEscalator.h"
#include "pattern/PatternEscalatorRainbow.h"
#include "pattern/PatternK2000.h"
#include "pattern/PatternWorms.h"
#include "pattern/PatternFireworks.h"

#include <OctoWS2811.h>

// globals of octows2811
DMAMEM int displayMemory[NBLEDS*6];
int drawingMemory[NBLEDS*6];
OctoWS2811 leds(NBLEDS, displayMemory, drawingMemory, WS2811_GRB | WS2811_800kHz);

// patterns
int aLight[] = {1, 2, 4, 6, 15, 25, 35, 50};
int wormsSections[] = { 1, 5, 10, 15, 9, 5, 4, 6, 7, 30 };

Pattern *patterns[] = {
  new PatternEscalator(),
  new PatternEscalatorRainbow(20,   1*1000,     1000, 2, 1.0),
  new PatternEscalatorRainbow(30,  30*1000,        1, 7, 2.0),
  new PatternK2000(HUE_RED, aLight, sizeof(aLight) / sizeof(aLight[0])),
  new PatternWorms(NBLEDS / 20, wormsSections, sizeof(wormsSections) / sizeof(wormsSections[0]), 30),
  new PatternFireworks()
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
    if (motionBottom > MOTION_DETECTION_THRESHOLD || motionTop > MOTION_DETECTION_THRESHOLD)
    {
      // motion detected
      int chosen = random(0, nbpatterns);
      dbg1("MOTION DETECTED, chosen pattern: %d", chosen);
      patterns[chosen]->run();
    }

    // shut all strips off
    ledsClear();
    leds.show();

    // poweroff led, and wait 100ms before polling again
    digitalWrite(TEENSY_LED_PIN, LOW);
    // just to get better pseudo random numbers when we need those:
    rand(); // FIXME will get optimized out, how to avoid that ?
    delayMicroseconds(1000 * 100);
  }
}


