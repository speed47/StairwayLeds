#ifndef _PATTERN_FIREWORKS_H
#define _PATTERN_FIREWORKS_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternFireworks : public Pattern
{
public:
    PatternFireworks(unsigned int delay = 15, unsigned long duration = 6000, float _dimSpeed = 0.5);

    virtual inline const char* name() { return "Fireworks"; }

protected:
    unsigned int _delay; // ms
    unsigned long _duration; // ms
    float _dimSpeed; // luminosity units/ms

    virtual void _animate(direction_t direction);
};

#endif
