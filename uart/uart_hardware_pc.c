#include "uart_hardware.h"
#include "../common_code/common.h"

#include "stdint.h"
uint8_t buf[50];
static int index_write = 0;
static int index_read = 0;

/** Buffer de reception de l'UART
 */
uint8_t UART_BUFF;

uint8_t get_uart()
{
    // réactiver les interruption ?
    return buf[index_read++];
}

void uart_send_byte(uint8_t byte)
{
    debug_byte(byte);
    buf[index_write++] = byte;
}
