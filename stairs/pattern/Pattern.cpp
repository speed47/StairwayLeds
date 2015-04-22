#include <limits.h>
#include "Pattern.h" // myself
#include "Arduino.h" // millis()
#include "printbuf.h" // dbg*
#include "globals.h" // ledsClear

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
  ledsClear(); // just in case
  this->_iterations = 0;
  this->_overflowAdjust = 0;
  this->_animationStart = millis();
  this->_animate();
  unsigned long elapsedNoZero = this->elapsed();
  if (elapsedNoZero == 0)
  {
    // should not happen, but avoid zerodiv just in case
    elapsedNoZero++;
  }
  dbg1("%s animation ran at %.1ffps (%lu iter in %lums)", this->name(),
    this->_iterations / (elapsedNoZero / 1000.0), this->_iterations, elapsedNoZero);
}

unsigned long Pattern::elapsed()
{
  if (millis() < this->_animationStart)
  {
    // handle millis() overflow
    this->_overflowAdjust = (ULONG_MAX - this->_animationStart);
    this->_animationStart = 0;
  }
  return millis() - this->_animationStart + this->_overflowAdjust;
}

