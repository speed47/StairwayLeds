#ifndef _HELPERS_H
#define _HELPERS_H

#ifndef _HEADER_OCTOWS2811_H
#define _HEADER_OCTOWS2811_H
#include <OctoWS2811.h>
#endif

#define POWERED_ON true
#define POWERED_OFF false

int findOneRandomPoweredLed(OctoWS2811 octo, bool onOrOff, int offset, int indexmin, int indexmax);

#endif
