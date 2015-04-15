#ifndef _PATTERN_ESCALATOR_H
#define _PATTERN_ESCALATOR_H

#include "Randomizer.h"

class PatternEscalator
{
public:
    PatternEscalator(int mainLuminosity=30, int glowLuminosity=50, float glowSpeed=1.5, int glowOften=1, Randomizer *mainHue = new Randomizer(0,360));
    void run();

private:
    int mainLuminosity;
    int glowLuminosity;
    float glowSpeed;
    int glowOften;

    Randomizer* mainHue;

    void _randomize();
    void _animate();
};

#endif
