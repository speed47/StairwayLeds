#ifndef _PATTERN_AIRPORT_H
#define _PATTERN_AIRPORT_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternAirport : public Pattern
{
public:
    PatternAirport(int anchorSpacing = 20, int anchorColorPassive = 0x1F1F1F, int anchorColorActive = 0xFFFFFF,
      int anchorNearColor = 0x20CC20, int wayColor = 0x400000, unsigned long interDelay = 2000);

protected:
    int _anchorSpacing;
    int _anchorColorPassive;
    int _anchorColorActive;
    int _anchorNearColor;
    int _wayColor;
    unsigned long interDelay; // ms

    virtual void _animate();
};

#endif
