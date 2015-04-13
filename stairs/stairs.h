#ifndef _STAIRS_H
#define _STAIRS_H

//#include <OctoWS2811.h>

void escalatordetector();
void escalatoronce(int direction);
void worms(int nbWorms, int wormsSections[], int wormsLength, int maxSlowness);
void k2000(int baseHue, int aLight[], int length);
void flashouilles();
void rainbow(int phaseShift, int cycleTime);

#endif
