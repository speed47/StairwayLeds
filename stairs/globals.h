#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <stdint.h>
#include <time.h>
#include <OctoWS2811.h>
#include "pattern/Pattern.h"

/* the 4 defines below should be managed by the Makefile
but just in case, define them if they are not */

#ifndef GIT_REVISION
# define GIT_REVISION none
#endif
#ifndef GIT_DIRTY
# define GIT_DIRTY unknown
#endif
#ifndef GIT_BRANCH
# define GIT_BRANCH nobranch
#endif
#if !defined(BUILD_TIME) && defined(TIME_T)
# define BUILD_TIME TIME_T
#endif

/* helpers */

#define _EXPAND2STR(str) #str
#define EXPAND2STR(str) _EXPAND2STR(str)

/* teensy restart magic */

#define CPU_RESTART_ADDR (uint32_t *)0xE000ED0C
#define CPU_RESTART_VAL 0x5FA0004
#define CPU_RESTART (*CPU_RESTART_ADDR = CPU_RESTART_VAL);

/* leds on the right strip (for now the only one) */
#define RIGHT_LEDS_COUNT 232
#define RIGHT_LEDS_OFFSET (RIGHT_LEDS_COUNT * 1)

/* leds on the left strip (TODO) */
#define LEFT_LEDS_COUNT 100
#define LEFT_LEDS_OFFSET (LEFT_LEDS_COUNT * 2)

/* compat for patterns supporting only 1 strip */
#define NBLEDS RIGHT_LEDS_COUNT
#define LEDS_OFFSET RIGHT_LEDS_OFFSET

/* motion detectors */
#define BOTTOM_MOTION_DETECTOR_PIN 23
#define    TOP_MOTION_DETECTOR_PIN 0
#define MOTION_DETECTION_THRESHOLD 1000

/* misc stuff */

#define TEENSY_LED_PIN 13

extern OctoWS2811 leds;

inline void ledsClear(void)
{
  for (int i = 0; i < NBLEDS; i++)
    leds.setPixel(LEDS_OFFSET + i, 0);
}


#endif

