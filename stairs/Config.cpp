#include <stdlib.h>
#include "Config.h"
#include "printbuf.h"

Config::Config()
{
  this->patterns = NULL;
  this->nb = 0;
}

Config::~Config()
{
  // TODO
}

void Config::addPattern(Pattern* newPattern)
{
  dbg3("addPattern: %d slots before", nb);
  nb++;
  this->patterns = (Pattern **)realloc(this->patterns, nb * sizeof(Pattern *));
  this->patterns[nb-1] = newPattern;
  dbg3("addPattern: %d slots after, last index: %p", nb, this->patterns[nb-1]);
}

