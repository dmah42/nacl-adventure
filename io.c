#include "io.h"

#include <stdarg.h>
#include <stdio.h>

#ifdef NATIVE_CLIENT
extern void PostScreenMessage(const char* message);
extern void PostConsoleMessage(const char* message);
#endif

void screen_printf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char buffer[2048];
  vsnprintf(buffer, 2048, fmt, args);
#ifdef NATIVE_CLIENT
  PostScreenMessage(buffer);
#else
  fputs(buffer, stdout);
#endif
  va_end(args);
}

void console_printf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char buffer[256];
  vsnprintf(buffer, 256, fmt, args);
#ifdef NATIVE_CLIENT
  PostConsoleMessage(buffer);
#else
  fputs(buffer, stdout);
#endif
  va_end(args);
}
