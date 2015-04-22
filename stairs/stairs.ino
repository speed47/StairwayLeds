#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

#include "pattern/PatternPlain.h"
#include "pattern/PatternEscalator.h"
#include "pattern/PatternEscalatorRainbow.h"
#include "pattern/PatternK2000.h"
#include "pattern/PatternWorms.h"
#include "pattern/PatternFireworks.h"
#include "pattern/PatternAirport.h"
#include "pattern/PatternDissolve.h"

#ifndef _HEADER_OCTOWS2811_H
#define _HEADER_OCTOWS2811_H
#include <OctoWS2811.h>
#endif

//#define TEST_MODE

// globals of octows2811
DMAMEM int displayMemory[NBLEDS*6];
int drawingMemory[NBLEDS*6];
OctoWS2811 leds(NBLEDS, displayMemory, drawingMemory, WS2811_GRB | WS2811_800kHz);

// patterns
int chase[] = {1, 2, 4, 6, 15, 25, 35, 50};
int worm[] = {1, 5, 10, 15, 30, 50};

Pattern *patterns[] = {
  //new PatternPlain(0xFFFFFF, 5000),
  new PatternDissolve(
    20,
    2000,
    new Randomizer(0,360),
    new Randomizer(1,50)
  ),
  new PatternEscalator(
    /*mainLuminosity*/ 30,
    /*glowLuminosity*/ 50,
    /*glowSpeed*/ 1.5,
    /*glowOften*/ 1,
    /*mainHue*/ new Randomizer(0, 360)
  ),
  new PatternEscalatorRainbow(
    /*mainLuminosity*/ 30,
    /*delayFirst*/ 15,
    /*delayLast*/ 15,
    /*hueMultiplier*/ 13,
    /*delayBetweenPhases*/ 2000
  ),
  new PatternEscalatorRainbow(
    /*mainLuminosity*/ 20,
    /*delayFirst*/ 1,
    /*delayLast*/ 1,
    /*hueMultiplier*/ 2,
    /*delayBetweenPhases*/ 2000
  ),
  new PatternK2000(
    /*chase*/ chase,
    /*chaseLen*/ sizeof(chase) / sizeof(chase[0]),
    /*duration*/ 8000,
    /*delay*/ 4,
    /*hueStep*/ 3
  ),
  new PatternWorms(
    /*nbWorms*/ 15,
    /*worm*/ worm,
    /*wormLen*/ sizeof(worm) / sizeof(worm[0]),
    /*maxSlowness*/ 20
  ),
  new PatternFireworks(
    /*probability*/ 10,
    /*delay*/ 15,
    /*duration*/ 6000
  ),
  new PatternAirport(
    /*anchorSpacing*/ 15,
    /*anchorPassiveColor*/ 0x111111,
    /*anchorActiveColor*/  0xFFFFFF,
    /*anchorActiveDuration*/  100,
    /*anchorPassiveDuration*/ 600,
    /*anchorNearColor*/ 0x300000, //0x003000,
    /*wayColor*/        0x000002, //makeColor(HUE_GREEN, 100, 1), //makeColor(HUE_RED,   100, 1),   
    /*delayBetweenPhases*/      2000
  )
};

// kill useless func
void yield()
{
}

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
  // patterns
  dbg1("got %d different patterns", sizeof(patterns) / sizeof(patterns[0]));
  // done
  dbg1(code_version());
  dbg1("setup done");
}

void loop()
{
  int nbpatterns = sizeof(patterns) / sizeof(patterns[0]);

#ifdef TEST_MODE
  dbg1("waiting for screen to be attached");
  delay(3000); // leave time for screen to be attached
  while (1)
  {
    dbg1(code_version());
    for (int c = 0; c < nbpatterns; c++)
    {
      dbg1("TEST MODE, running pattern %d (%s)", c, patterns[c]->name());
      patterns[c]->run();
      // shut all strips off
      ledsClear();
      leds.show();
      dbg1("sleeping");
      delay(1000);
    }
  }

#else

  int motionBottom, motionTop;
  int versionCounter = 0;
  while (1)
  {
    // power-on teensy led
    digitalWrite(TEENSY_LED_PIN, HIGH);
    // read detectors
    motionBottom = analogRead(BOTTOM_MOTION_DETECTOR_PIN);
    motionTop    = 0;//analogRead(   TOP_MOTION_DETECTOR_PIN);
    // output version from time to time
    if (versionCounter++ % 20 == 0)
    {
      dbg1("Running code version %s", code_version());
    }

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
    rand();
    // and sleep before polling for motion again
    delay(100);
  }
#endif
}


