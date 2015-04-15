#include "Randomizer.h"
#include "Arduino.h"

Randomizer::Randomizer(int vmin = 0, int vmax = 10) : vmin(vmin), vmax(vmax)
{
  this->value = 0;
}

void Randomizer::randomize()
{
  this->value = random(this->vmin, this->vmax);
}

