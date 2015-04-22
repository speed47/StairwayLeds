#ifndef _PATTERN_H
#define _PATTERN_H

class Pattern
{
public:
    Pattern(int ledsPerMeter = 60, float humanWalkingSpeed = 0.72);
    ~Pattern();

    virtual inline const char* name() { return "Pattern"; }
    unsigned long elapsed(); // returns ms since animation started
    virtual void run(); // main func

protected:
    int _ledsPerMeter;
    float _humanWalkingSpeed;
    unsigned long _animationStart;
    unsigned long _iterations;
    unsigned long _overflowAdjust;

    virtual void _animate() = 0; // pure virtual, must be defined in child
};

#endif
