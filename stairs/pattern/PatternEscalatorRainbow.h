#ifndef _PATTERN_ESCALATOR_RAINBOW_H
#define _PATTERN_ESCALATOR_RAINBOW_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternEscalatorRainbow : public Pattern
{
public:
    PatternEscalatorRainbow(int mainLuminosity=30, int delayFirst=100, int delayLast=0, int hueMultiplier=7, unsigned int delayBetweenPhases=2000);

    static inline const char* name() { return __FILE__; }

protected:
    int _mainLuminosity;
    int _delayFirst;
    int _delayLast;
    int _hueMultiplier;
    unsigned int _delayBetweenPhases;

    virtual void _animate();
};

#endif
