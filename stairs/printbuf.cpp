#include "globals.h"
#include "printbuf.h"

#include <stdio.h>
#include <kinetis.h>
#include <HardwareSerial.h>
#include <core_pins.h>

// buffer used and returned by printbuf() and printbufva()
char _print_buffer[PRINT_BUFFER_SIZE];

// used as sprintf() (return a char *) but buffer doesn't need to be specified
char *printbuf(const char *format, ...)
{
  va_list args;

  va_start(args, format);
  vsniprintf(_print_buffer, PRINT_BUFFER_SIZE, format, args);
  va_end(args);

  return _print_buffer;
}

// same as printbuf() but with already initialized va_list (used by dbg() func below)
char *printbufva(const char *format, va_list args)
{
  vsniprintf(_print_buffer, PRINT_BUFFER_SIZE, format, args);
  return _print_buffer;
}

// also see dbg1/dbg2/dbg3 macros
void dbg(int level, const char *format, ...)
{
  // if currently configured debug level is below this message debug level, skip it
  /*
  if (cfg.debug_level < level)
  {
    return;
  }
  */
  va_list args;

  unsigned long now = millis();
  Serial.print( printbuf("[%5lu.%03d] dbg%d: ", now/1000, (int)((now/1000.0 - now/1000) * 1000), level) );
  va_start(args, format);
  Serial.print( printbufva(format, args) );
  va_end(args);
  Serial.print( "\r\n" );
}


