#include "Pattern.h"

Pattern::Pattern(int ledsPerMeter, float humanWalkingSpeed) : ledsPerMeter(ledsPerMeter), humanWalkingSpeed(humanWalkingSpeed)
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
  this->_animate();
}

void Pattern::_randomize()
{
  // noop by default
}

