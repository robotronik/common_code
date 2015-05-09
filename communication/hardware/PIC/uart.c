#include <p33FJ128MC802.h>

#include "common_code/time.h"

#include "uart.h"

////////////////////////////////////////////////////////////////////////////////

/**
 * Envoie un caractère dans l'UART
 */
static void UART_putc(unsigned char c);

////////////////////////////////////////////////////////////////////////////////

static void UART_putc(unsigned char c)
{
    while (U1STAbits.UTXBF);
        U1TXREG = c;

    return;
}

////////////////////////////////////////////////////////////////////////////////

void UART_send_message(char* message) {
    char *actuel = message;
    while (*actuel)
        UART_putc(*actuel++);

    // Il est bisarement necessaire de faire une pause après chaque envoie
    pause_ms(1);
}

