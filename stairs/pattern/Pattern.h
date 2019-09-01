#ifndef _PATTERN_H
#define _PATTERN_H

#include "../globals.h"

class Pattern
{
public:
    Pattern(int ledsPerMeter = 60, float humanWalkingSpeed = 0.8);
    ~Pattern();

    virtual inline const char* name() { return "Pattern"; }
    unsigned long elapsed(); // returns ms since animation started
    virtual void run(direction_t direction); // main func

protected:
    int _ledsPerMeter;
    float _humanWalkingSpeed;
    unsigned long _animationStart;
    unsigned long _iterations;
    unsigned long _overflowAdjust;

    virtual void _animate(direction_t direction) = 0; // pure virtual, must be defined in child
};

#endif
