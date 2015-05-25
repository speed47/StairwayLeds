#include "globals.h"
#include "helpers.h"

int findOneRandomPoweredLed(direction_t direction, bool onOrOff, int offset, int indexmin, int indexmax)
{
  int ledCandidate = random(indexmin, indexmax);
  int dir = random(0,2) == 1 ? 1 : -1;
  // is it lit (or off) already ?
  while (ledCandidate >= indexmin && ledCandidate < indexmax)
  {
    if (onOrOff == POWERED_OFF && getPix(direction, offset, ledCandidate) == 0x000000)
    {
      // it's off, found !
      return ledCandidate;
    }
    else if (onOrOff == POWERED_ON && getPix(direction, offset, ledCandidate) != 0x000000)
    {
      // it's on, found !
      return ledCandidate;
    }
    // find the closer one in specified dir
    ledCandidate += dir;
  }
  // damn, we are at an extremity, go back the other way !
  ledCandidate -= dir;
  while (ledCandidate >= indexmin && ledCandidate < indexmax)
  {
    if (onOrOff == POWERED_OFF && getPix(direction, offset, ledCandidate) == 0x000000)
    {
      // it's off, found !
      return ledCandidate;
    }
    else if (onOrOff == POWERED_ON && getPix(direction, offset, ledCandidate) != 0x000000)
    {
      // it's on, found !
      return ledCandidate;
    }
    // find the closed one in specified reverse dir
    ledCandidate -= dir;
  }
  // at the other extremity now ?? ok, so actually everybody is lit (or off). STOOOOOP
  return -1;
}

