#ifndef _PATTERN_ESCALATOR_RAINBOW_H
#define _PATTERN_ESCALATOR_RAINBOW_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternEscalatorRainbow : public Pattern
{
public:
    PatternEscalatorRainbow(int mainLuminosity=30, int delayFirst=100*1000, int delayLast=0, int hueMultiplier=7, float delayBetweenPhases=2.0);

protected:
    int _mainLuminosity;
    int _delayFirst;
    int _delayLast;
    int _hueMultiplier;
    float _delayBetweenPhases;

    virtual void _animate();
};

#endif
