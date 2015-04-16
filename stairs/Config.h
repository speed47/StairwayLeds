#ifndef _CONFIG_H
#define _CONFIG_H

#include "pattern/Pattern.h"

class Config
{
  public:
    Pattern** patterns;
    int nb();

    Config();
    ~Config();

    void addPattern(Pattern* newPattern);

  protected:
    int _nb;
};


#endif
