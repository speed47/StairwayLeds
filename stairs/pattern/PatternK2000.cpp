#include <limits.h>
#include "PatternK2000.h"
#include "Arduino.h"
#include "globals.h"
#include "makeColor.h"
#include "printbuf.h"

PatternK2000::PatternK2000(int *chase, int _chaseLen, unsigned int duration, unsigned int delay, int hueStep) :
  _chase(chase), _chaseLen(_chaseLen), _duration(duration), _delay(delay), _hueStep(hueStep)
{
}

void PatternK2000::_animate()
{
  int currentDirection = 1;
  int hue = random(0, 361);
  int k[_chaseLen];

  // setup the head and tail  
  for (int i = 0; i < _chaseLen; i++)
  {
    k[i] = i;
  }
  
  while (this->elapsed() < _duration)
  {
    digitalWrite(TEENSY_LED_PIN, HIGH);
    this->_iterations++;
    hue = hue + _hueStep % 360;
    // reverse direction if we're at the top
    if (k[_chaseLen-1] >= NBLEDS - 1)
    {
      currentDirection = -1; // down
    }
    // reverse direction if we're at the bottom
    else if (k[_chaseLen-1] <= 0)
    {
      currentDirection = 1; // up
    }
    
    // before advancing the tail, power off the last tail led
    // the others are either already black or will still be part
    // of the lighted leds of this step
    leds.setPixel(LEDS_OFFSET + k[0], 0);
    
    // advance the tail
    for (int i = 0; i < _chaseLen - 1; i++)
    {
      k[i] = k[i+1];
    }
    // and set the head
    k[_chaseLen-1] += currentDirection;
    
    // set the colors now, from tail to head
    // because the head must always have the last word
    for (int i = 0; i < _chaseLen; i++)
    {
      leds.setPixel(LEDS_OFFSET + k[i], makeColor(hue, 100, _chase[i]));
    }
    
    // now display
    leds.show();
    digitalWrite(TEENSY_LED_PIN, LOW);
    delay(_delay);
  }
}
  
