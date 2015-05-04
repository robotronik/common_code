#include <stdio.h>
#include <stdarg.h>

#include "../debug.h"

#include "text_emission.h"
#include "uart.h"

#define BUFF_SIZE 40

void send_text(const char *format, ...)
{
    va_list args;
    char buff[BUFF_SIZE];

    va_start(args, format);
    int nb_char = vsnprintf(buff, BUFF_SIZE, format, args);
    debug(_VERBOSE_, "envoie du message ---%s---", buff);
    uart_send_message(buff, nb_char);
    va_end(args);
}
