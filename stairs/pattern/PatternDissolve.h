#ifndef _PATTERN_DISSOLVE_H
#define _PATTERN_DISSOLVE_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternDissolve : public Pattern
{
public:
    PatternDissolve(unsigned int delay = 50, unsigned int delayBetweenPhases = 2000, Randomizer* colorPicker = new Randomizer(0,360), Randomizer* luminosityPicker = new Randomizer(1,50));
    ~PatternDissolve();

    virtual inline const char* name() { return "Dissolve"; }

protected:
    unsigned int _delay;
    unsigned int _delayBetweenPhases;
    Randomizer* _colorPicker;
    Randomizer* _luminosityPicker;

    virtual void _animate();
};

#endif
