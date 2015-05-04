#include <stdio.h>

#include "uart.h"

void uart_send_message(char *msg, int nb_char)
{
    (void) nb_char; // pour éviter un warning inutile
    puts(msg);
}
