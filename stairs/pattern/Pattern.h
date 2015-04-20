#ifndef _PATTERN_H
#define _PATTERN_H

class Pattern
{
public:
    Pattern(int ledsPerMeter = 60, float humanWalkingSpeed = 0.72);
    ~Pattern();

    static inline const char* name() { return __FILE__; }
    unsigned long elapsed(); // returns ms since animation started
    virtual void run(); // main func

protected:
    virtual void _randomize();
    virtual void _animate() = 0; // pure virtual, must be defined in child

    int _ledsPerMeter;
    float _humanWalkingSpeed;
    unsigned long _animationStart;
    unsigned long _iterations;
};

#endif
