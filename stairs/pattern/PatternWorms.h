#ifndef _PATTERN_WORMS_H
#define _PATTERN_WORMS_H

#include "Pattern.h"
#include "Randomizer.h"
#include "globals.h"

class PatternWorms : public Pattern
{
public:
    PatternWorms(int nbWorms = NBLEDS / 20, int* wormsSections = NULL, int wormsSectionsLen = 0, int maxSlowness = 30);

protected:
    int nbWorms;
    int *wormsSections;
    int wormsSectionsLen;
    int maxSlowness;

    virtual void _animate();
};

#endif
