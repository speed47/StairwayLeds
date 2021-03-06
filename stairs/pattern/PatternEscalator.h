#ifndef _PATTERN_ESCALATOR_H
#define _PATTERN_ESCALATOR_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternEscalator : public Pattern
{
public:
    PatternEscalator(int mainLuminosity=30, int glowLuminosity=50, float glowSpeed=1.5, int glowOften=1, Randomizer *mainHue = new Randomizer(0,360));
    ~PatternEscalator();

    virtual inline const char* name() { return "Escalator"; }

protected:
    int mainLuminosity;
    int glowLuminosity;
    float glowSpeed;
    int glowOften;

    Randomizer* mainHue;

    virtual void _animate(direction_t direction);
};

#endif
