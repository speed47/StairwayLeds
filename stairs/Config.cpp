#include <stdlib.h>
#include "Config.h"
#include "printbuf.h"

Config::Config()
{
  this->patterns = NULL;
  this->_nb = 0;
}

Config::~Config()
{
  // TODO
}

void Config::addPattern(Pattern* newPattern)
{
  dbg3("addPattern: %d slots before", _nb);
  _nb++;
  this->patterns = (Pattern **)realloc(this->patterns, _nb * sizeof(Pattern *));
  this->patterns[_nb-1] = newPattern;
  dbg3("addPattern: %d slots after (really: %d), last index: %p", _nb, sizeof(this->patterns), this->patterns[_nb-1]);
}

int Config::nb()
{
  return _nb;
}

