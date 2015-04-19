#include <limits.h>
#include "Pattern.h" // myself
#include "Arduino.h" // millis()

Pattern::Pattern(int ledsPerMeter, float humanWalkingSpeed) :
  _ledsPerMeter(ledsPerMeter), _humanWalkingSpeed(humanWalkingSpeed), _animationStart(0)
{
}

Pattern::~Pattern()
{
  // nothing to do
}

void Pattern::run()
{
  // simple case (can be overriden)
  this->_randomize();
  this->_animationStart = millis();
  this->_animate();
}

void Pattern::_randomize()
{
  // noop by default
}

unsigned long Pattern::elapsed()
{
  static unsigned long overflowAdjust = 0;
  if (millis() < this->_animationStart)
  {
    // handle millis() overflow
    overflowAdjust = (ULONG_MAX - this->_animationStart);
    this->_animationStart = 0;
  }
  return millis() - this->_animationStart + overflowAdjust;
}

