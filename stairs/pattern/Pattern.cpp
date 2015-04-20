#include <limits.h>
#include "Pattern.h" // myself
#include "Arduino.h" // millis()
#include "printbuf.h" // dbg*

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
  this->_iterations = 0;
  this->_animationStart = millis();
  this->_animate();
  //dbg2("bugged ? anistart=%lu iter=%lu", this->_animationStart, this->_iterations);
  unsigned long elapsedNoZero = this->elapsed();
  if (elapsedNoZero == 0)
  {
    // should not happen, but avoid zerodiv just in case
    elapsedNoZero++;
  }
  dbg1("%s animation ran at %.1ffps (%lu iter in %lums)", this->name(),
    this->_iterations / (elapsedNoZero / 1000.0), this->_iterations, elapsedNoZero);
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

