#ifndef _PATTERN_FIREWORKS_H
#define _PATTERN_FIREWORKS_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternFireworks : public Pattern
{
public:
    PatternFireworks(int probability = 10, unsigned int delay = 15, unsigned long duration = 4000);

    virtual inline const char* name() { return "Fireworks"; }

protected:
    int _probability;
    unsigned int _delay; // ms
    unsigned long _duration; // ms

    virtual void _animate();
};

#endif
