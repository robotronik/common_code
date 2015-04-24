#ifndef UART_HARDWARE_H
#define UART_HARDWARE_H

#include "stdint.h"

/** Lit la valeur courante de l'uart
 */
uint8_t get_uart();

/** Envoie un byte dans l'uart
 */
void uart_send_byte(uint8_t byte);

#endif // UART_HARDWARE_H
