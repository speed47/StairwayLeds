#include "helpers.h"

int findOneRandomPoweredLed(OctoWS2811 octo, bool onOrOff, int offset, int indexmin, int indexmax)
{
  int ledCandidate = random(indexmin, indexmax);
  int direction = random(0,2) == 1 ? 1 : -1;
  // is it lit (or off) already ?
  while (ledCandidate >= indexmin && ledCandidate < indexmax)
  {
    if (onOrOff == POWERED_OFF && octo.getPixel(offset + ledCandidate) == 0x000000)
    {
      // it's off, found !
      return ledCandidate;
    }
    else if (onOrOff == POWERED_ON && octo.getPixel(offset + ledCandidate) != 0x000000)
    {
      // it's on, found !
      return ledCandidate;
    }
    // find the closer one in specified direction
    ledCandidate += direction;
  }
  // damn, we are at an extremity, go back the other way !
  ledCandidate -= direction;
  while (ledCandidate >= indexmin && ledCandidate < indexmax)
  {
    if (onOrOff == POWERED_OFF && octo.getPixel(offset + ledCandidate) == 0x000000)
    {
      // it's off, found !
      return ledCandidate;
    }
    else if (onOrOff == POWERED_ON && octo.getPixel(offset + ledCandidate) != 0x000000)
    {
      // it's on, found !
      return ledCandidate;
    }
    // find the closed one in specified reverse direction
    ledCandidate -= direction;
  }
  // at the other extremity now ?? ok, so actually everybody is lit (or off). STOOOOOP
  return -1;
}

