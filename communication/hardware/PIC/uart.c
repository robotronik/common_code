#include <p33FJ128MC802.h>

#include "common_code/time.h"

#include "uart.h"

#define INT_UART_TX
#define RX_BUFFER_SIZE 16
#define TX_BUFFER_SIZE 40

////////////////////////////////////////////////////////////////////////////////

/**
 * Envoie un caractère dans l'UART
 */
static void UART_putc(unsigned char c);

static unsigned char rxBuffer[RX_BUFFER_SIZE];
static unsigned short indexRxBuffer = 0;
static unsigned short rxBufferLength = 0;

#ifdef INT_UART_TX
static unsigned char txBuffer[TX_BUFFER_SIZE];
static unsigned short indexTxBuffer = 0;
static unsigned short txBufferLength = 0;
#endif

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

void UART_init()
{
    AD1PCFGLbits.PCFG5 = 1;	// Désactivation de l'entrée analogique !!!
    RPOR1bits.RP2R = 3;							// Tx1 -> RP2
    RPINR18bits.U1RXR = 3;						// RP3 -> Rx1

    //U1MODEbits.LPBACK = 1;	// Debug : Tx1 -> Rx1

    // Low speed : BRG = 79,23 MHz / 32 / Baudrate - 1
    U1MODEbits.BRGH = 1;	// High speed : BRG = 79,23 MHz / 8 / Baudrate - 1
    U1BRG = 85; 			// BAUD Rate Setting for 115200 gives 115160 bauds

#ifdef INT_UART_TX
    U1STAbits.UTXISEL1 = 1;	// Interrupt on empty FIFO, last byte is being sent
    U1STAbits.UTXISEL0 = 0;	//                      "
#endif //#ifdef INT_UART_TX

    IFS0bits.U1RXIF = 0; 	// On evite des interruptions à l'activation
    IEC0bits.U1RXIE = 1;	// Activation de l'interruption sur réceptions
#ifdef INT_UART_TX
    IFS0bits.U1TXIF = 0;
    IEC0bits.U1TXIE = 1;	// Activation de l'interruption sur l'envoie
#endif //#ifdef INT_UART_TX
    //IFS4bits.U1EIF = 0;
    //IEC4bits.U1EIE = 1;	// Activation de l'interruption sur erreurs

    U1MODEbits.UARTEN = 1; 	// Enable UART
    U1STAbits.UTXEN = 1; 	// Enable UART TX
}

int UART_getc(unsigned char *byte) {
    if (rxBufferLength) {
        *byte = rxBuffer[indexRxBuffer];
        IEC0bits.U1RXIE = 0;    // Désactivation de l'interruption pour modifier les variables globales
        rxBufferLength --;
        indexRxBuffer ++; indexRxBuffer %= RX_BUFFER_SIZE;
        IEC0bits.U1RXIE = 1;    // Activation de l'interruption
        return 1;
    }
    return 0;
}

void __attribute__((interrupt, auto_psv)) _U1RXInterrupt()
{
    IFS0bits.U1RXIF = 0; // On s'acquitte de l'interruption

    if(U1STAbits.FERR == 1) // Erreurs ?
        return ;
    /* must clear the overrun error to keep uart receiving */
    if(U1STAbits.OERR == 1)
    {
        U1STAbits.OERR = 0;
        return ;
    }

    // Attention, il ne faut accéder UNE SEULE fois au registre U1RXREG.
    // get the data
    /*
       if(U1STAbits.URXDA == 1) {
       rxBuffer[(indexRxBuffer + rxBufferLength) % RX_BUFFER_SIZE] = U1RXREG;
       rxBufferLength ++;
       }
       */
    if(U1STAbits.URXDA == 1)
        s2a_lecture_message(U1RXREG);
}

void __attribute__((interrupt, auto_psv)) _U1ErrInterrupt()
{
    IFS4bits.U1EIF = 0; // On s'acquitte de l'interruption
    if(U1STAbits.FERR == 1) // Erreurs ?
        return ;
    // must clear the overrun error to keep uart receiving
    if(U1STAbits.OERR == 1)
        U1STAbits.OERR = 0;
    //error();

}

#ifdef INT_UART_TX
void __attribute__((interrupt, auto_psv)) _U1TXInterrupt()
{
    IFS0bits.U1TXIF = 0; // On s'acquitte de l'interruption

    if(U1STAbits.FERR == 1) // Erreurs ?
        return ;
    // must clear the overrun error to keep uart receiving
    if(U1STAbits.OERR == 1)
    {
        U1STAbits.OERR = 0;
        return ;
    }

    while (txBufferLength && !U1STAbits.UTXBF) {            // Si le buffer du module n'est pas plein
        U1TXREG = txBuffer[indexTxBuffer];
        txBufferLength --;
        indexTxBuffer ++; indexTxBuffer %= TX_BUFFER_SIZE;
    }
}
#endif //#ifdef INT_UART_TX
