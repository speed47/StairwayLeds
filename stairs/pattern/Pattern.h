#ifndef _PATTERN_H
#define _PATTERN_H

class Pattern
{
public:
    Pattern(int ledsPerMeter = 60, float humanWalkingSpeed = 0.72);
    ~Pattern();
    virtual void run();

protected:
    virtual void _randomize();
    virtual void _animate() = 0; // pure virtual

    int ledsPerMeter;
    float humanWalkingSpeed;
};

#endif
