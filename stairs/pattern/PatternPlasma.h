#ifndef _PATTERN_PLASMA_H
#define _PATTERN_PLASMA_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternPlasma : public Pattern
{
public:
    PatternPlasma();

    virtual inline const char* name() { return "Plasma"; }

protected:

    virtual void _animate();
};

#endif
