#ifndef _PATTERN_PLASMA_H
#define _PATTERN_PLASMA_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternPlasma : public Pattern
{
public:
    PatternPlasma(unsigned int duration = 5000);

    virtual inline const char* name() { return "Plasma"; }

protected:
    unsigned int _duration;

    virtual void _animate();
};

#endif
