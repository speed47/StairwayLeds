#ifndef _PRINTBUF_H
#define _PRINTBUF_H

#include <stdarg.h>

#define PRINT_BUFFER_SIZE 128

#define DEBUG_LEVEL_1 1
#define DEBUG_LEVEL_2 2
#define DEBUG_LEVEL_3 3

// should be defined via ./configure, but if not, here is a default
#ifndef STAIRS_DEBUG
# define STAIRS_DEBUG DEBUG_LEVEL_3
#endif

#if STAIRS_DEBUG >= DEBUG_LEVEL_1
# define dbg1(...) dbg(1, __VA_ARGS__)
#else
# define dbg1(...) ;
#endif

#if STAIRS_DEBUG >= DEBUG_LEVEL_2
# define dbg2(...) dbg(2, __VA_ARGS__)
#else
# define dbg2(...) ;
#endif

#if STAIRS_DEBUG >= DEBUG_LEVEL_3
# define dbg3(...) dbg(3, __VA_ARGS__)
#else
# define dbg3(...) ;
#endif

char *printbuf(const char *format, ...);
char *printbufva(const char *format, va_list args);
void dbg(int level, const char *format, ...);

#endif
