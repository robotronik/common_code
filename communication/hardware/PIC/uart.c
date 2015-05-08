#include <stdio.h>

#include <p33FJ128MC802.h>

#include "uart.h"

////////////////////////////////////////////////////////////////////////////////

#define INT_UART_TX
#define TX_BUFFER_SIZE 64

/**
 * Envoie un caractère dans l'UART
 */
static void UART_putc(unsigned char c);

////////////////////////////////////////////////////////////////////////////////

static void UART_putc(unsigned char c)
{
#ifdef INT_UART_TX
    static unsigned char txBuffer[TX_BUFFER_SIZE];
    static unsigned short txBufferLength = 0;
    static unsigned short indexTxBuffer = 0;

    if(txBufferLength || U1STAbits.UTXBF) {         // Si la file contient une donnée ou que le buffer du périphérique est plein
        while (txBufferLength >= TX_BUFFER_SIZE);
        IEC0bits.U1TXIE = 0;    // Désactivation de l'interruption pour modifier les variables globales
        txBuffer[(indexTxBuffer + txBufferLength) % TX_BUFFER_SIZE] = c;
        txBufferLength ++;
        IEC0bits.U1TXIE = 1;    // Activation de l'interruption
        return;
    } else U1TXREG = c;

#else //#ifdef INT_UART_TX
    while (U1STAbits.UTXBF);
        U1TXREG = c;
#endif //#ifdef INT_UART_TX

    return;
}

////////////////////////////////////////////////////////////////////////////////

void UART_send_message(char* message) {
    char *actuel = message;
    while (*actuel)
        UART_putc(*actuel++);
}

