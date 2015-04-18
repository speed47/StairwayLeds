#ifndef _PATTERN_K2000_H
#define _PATTERN_K2000_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternK2000 : public Pattern
{
public:
    PatternK2000(int baseHue = 200, int* aLight = (int *)0, int aLightLen = 0);

protected:
    int baseHue;
    int* aLight;
    int aLightLen;

    virtual void _animate();
};

#endif
