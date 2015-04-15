#ifndef _PATTERN_ESCALATOR_RAINBOW_H
#define _PATTERN_ESCALATOR_RAINBOW_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternEscalatorRainbow : public Pattern
{
public:
    PatternEscalatorRainbow(int mainLuminosity=30);
    ~PatternEscalatorRainbow();

protected:
    int mainLuminosity;

    virtual void _animate();
};

#endif
