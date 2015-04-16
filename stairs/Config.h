#ifndef _CONFIG_H
#define _CONFIG_H

#include "pattern/Pattern.h"

class Config
{
  public:
    Pattern** patterns;

    Config();
    ~Config();

    void addPattern(Pattern* newPattern);

  protected:
    int nb;
};


#endif
