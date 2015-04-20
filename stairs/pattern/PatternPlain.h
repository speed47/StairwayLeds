#ifndef _PATTERN_PLAIN_H
#define _PATTERN_PLAIN_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternPlain : public Pattern
{
public:
    PatternPlain(int color = 0xFFFFFF, unsigned int duration = 5000);

    virtual inline const char* name() { return "Plain"; }

protected:
    int _color;
    unsigned int _duration;

    virtual void _animate();
};

#endif
