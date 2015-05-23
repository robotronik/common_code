#include <stdio.h>

void UART_send_message(char *msg, unsigned int nb_char)
{
    (void) nb_char; // pour éviter un warning inutile
    puts(msg);
}
