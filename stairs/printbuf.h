#ifndef _PRINTBUF_H
#define _PRINTBUF_H

#include <stdarg.h>

#define PRINT_BUFFER_SIZE 128

#define DEBUG_NONE  0
#define DEBUG_1     1
#define DEBUG_2     2
#define DEBUG_3     3

// should be defined via ./configure, but if not, here is a default
#ifndef PROJECT_DEBUG
# define PROJECT_DEBUG DEBUG_2
#endif

char *printbuf(const char *format, ...)
	__attribute__ ((format (printf, 1, 2)));

char *printbufva(const char *format, va_list args);

void dbgva(int level, const char *format, va_list args);

void dbg(int level, const char *format, ...)
	__attribute__ ((format (printf, 2, 3)));

inline void dbg1(const char *format, ...) __attribute__ ((format (printf, 1, 2)));
inline void dbg1(const char *format, ...)
{
#if PROJECT_DEBUG >= DEBUG_1
	va_list args;
	va_start(args,format);
	dbgva(1, format, args);
	va_end(args);
#endif
}

inline void dbg2(const char *format, ...) __attribute__ ((format (printf, 1, 2)));
inline void dbg2(const char *format, ...)
{
#if PROJECT_DEBUG >= DEBUG_2
	va_list args;
	va_start(args,format);
	dbgva(2, format, args);
	va_end(args);
#endif
}

inline void dbg3(const char *format, ...) __attribute__ ((format (printf, 1, 2)));
inline void dbg3(const char *format, ...)
{
#if PROJECT_DEBUG >= DEBUG_3
	va_list args;
	va_start(args,format);
	dbgva(3, format, args);
	va_end(args);
#endif
}


#endif
