#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <stdint.h>
#include <time.h>
#include <OctoWS2811.h>
#include "pattern/Pattern.h"

#ifndef GIT_REVISION
# define GIT_REVISION none
#endif
#ifndef GIT_DIRTY
# define GIT_DIRTY unknown
#endif
#if !defined(BUILD_TIME) && defined(TIME_T)
# define BUILD_TIME TIME_T
#endif

#define _EXPAND2STR(str) #str
#define EXPAND2STR(str) _EXPAND2STR(str)

#define CPU_RESTART_ADDR (uint32_t *)0xE000ED0C
#define CPU_RESTART_VAL 0x5FA0004
#define CPU_RESTART (*CPU_RESTART_ADDR = CPU_RESTART_VAL);

#define NBLEDS 232
#define BOTTOM_MOTION_DETECTOR_PIN 23
#define    TOP_MOTION_DETECTOR_PIN 0
#define TEENSY_LED_PIN 13
#define DETECTION_THRESHOLD 1000

#define DIRECTION_BOTTOM_TO_TOP 1

#define LEDS_OFFSET NBLEDS


typedef struct
{
  int debug_level;
  // list of available patterns
  Pattern* patterns[16];
} config_t;

extern OctoWS2811 leds;

extern config_t cfg;
extern const int ledsPerMeter;
extern const float humanWalkingSpeed;

#endif

