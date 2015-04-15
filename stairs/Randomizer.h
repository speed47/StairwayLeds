#ifndef _RANDOMIZER_H
#define _RANDOMIZER_H

class Randomizer
{
public:
    int value;

    Randomizer(int vmin, int vmax);
    void randomize();

private:
  int vmin;
  int vmax;
};

#endif
