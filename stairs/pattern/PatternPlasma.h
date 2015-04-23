#ifndef _PATTERN_PLASMA_H
#define _PATTERN_PLASMA_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternPlasma : public Pattern
{
public:
    PatternPlasma(unsigned int delayBetweenPhases = 2000);

    virtual inline const char* name() { return "Plasma"; }

protected:
    unsigned int _delayBetweenPhases;

    virtual void _animate();
};

#endif
