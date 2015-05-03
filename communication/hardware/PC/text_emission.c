#include <stdio.h>
#include <stdarg.h>

#include "text_emission.h"


void send_text(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
