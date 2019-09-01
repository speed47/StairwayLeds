#ifndef _PATTERN_WORMS_H
#define _PATTERN_WORMS_H

#include "Pattern.h"
#include "Randomizer.h"
#include "globals.h"

class PatternWorms : public Pattern
{
public:
    PatternWorms(int nbWorms = NBLEDS / 20, int* worm = NULL, int wormLen = 0, int lowerSpeed = 30, unsigned int duration = 12000);

    virtual inline const char* name() { return "Worms"; }

protected:
    int _nbWorms;
    int *_worm;
    int _wormLen;
    int _lowerSpeed;
    unsigned int _duration;

    virtual void _animate(direction_t direction);
};

#endif
