#ifndef _HELPERS_H
#define _HELPERS_H

#ifndef _HEADER_OCTOWS2811_H
#define _HEADER_OCTOWS2811_H
#include <OctoWS2811.h>
#endif

#include "../globals.h"

#define POWERED_ON true
#define POWERED_OFF false

int findOneRandomPoweredLed(direction_t direction, bool onOrOff, int offset, int indexmin, int indexmax);

#endif
