#ifndef _PATTERN_K2000_H
#define _PATTERN_K2000_H

#include <stddef.h>
#include "Pattern.h"
#include "Randomizer.h"

class PatternK2000 : public Pattern
{
public:
    PatternK2000(int *chase = NULL, int chaseLen = 0, unsigned int duration = 5000, unsigned int delay = 4, int hueStep = 3);

    static inline const char* name() { return __FILE__; }

protected:
    int *_chase;
    int _chaseLen;
    unsigned int _duration;
    unsigned int _delay;
    int _hueStep;

    virtual void _animate();
};

#endif
