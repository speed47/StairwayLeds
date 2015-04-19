#ifndef _PATTERN_AIRPORT_H
#define _PATTERN_AIRPORT_H

#include "Pattern.h"
#include "Randomizer.h"

class PatternAirport : public Pattern
{
public:
    PatternAirport(int anchorSpacing = 20, int anchorPassiveColor = 0x1F1F1F, int anchorActiveColor = 0xFFFFFF,
      unsigned int anchorActiveDuration = 100, unsigned int anchorPassiveDuration = 500,
      int anchorNearColor = 0x20CC20, int wayColor = 0x400000, unsigned long interDelay = 2000);

protected:
    int _anchorSpacing;
    int _anchorPassiveColor;
    int _anchorActiveColor;
    unsigned int _anchorActiveDuration;
    unsigned int _anchorPassiveDuration;
    int _anchorNearColor;
    int _wayColor;
    unsigned long _interDelay; // ms

    virtual void _animate();
};

#endif
