#include "../common.h"

#include "emission_binaire.h"
#include "uart_hardware.h"

static void send_byte(uint8_t byte, uint8_t *crc);

void uart_send_msg(void *msg, int size_msg)
{
    uint8_t crc = 0;

    debug(1, "MESSAGE ENVOYÉ :\n");

    for (int i = 0; i < size_msg; i++) {
        send_byte(((uint8_t*)msg)[i], &crc);
    }

    debug(1, "CRC :\n");
    send_byte(crc, &crc);

    debug(1, "\\0 :\n");
    uart_send_byte('\0');

    debug(1, "\n\n");
}

static void send_byte(uint8_t byte, uint8_t *crc)
{
    switch (byte) {
        case '\\':
        case '\0':
            uart_send_byte('\\');
            *crc ^= '\\';

            // Dans tout les cas, l'étape suivante à lieu (pas de break
            // volontairement)
        default:
            uart_send_byte(byte);
            *crc ^= byte;
            break;
    }
}
