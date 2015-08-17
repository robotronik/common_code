#include <string.h>
#include <stdio.h>

#include "../../hardware/debug.h"

#include "text_emission.h"
#include "uart.h"

#define BUFF_SIZE 40
static char buff[BUFF_SIZE];

////////////////////////////////////////////////////////////////////////////////

void send_val(const char *val_key, int value)
{
    int size = snprintf(buff, BUFF_SIZE, "%s%d\n", val_key, value);
    UART_send_message(buff, size);
    debug(_DEBUG_, "envoie de la commande\n%s", buff);
}

void send_cmd(const char *commande_key)
{
    int size = snprintf(buff, BUFF_SIZE, "%s\n", commande_key);
    UART_send_message(buff, size);
    debug(_DEBUG_, "envoie de la commande\n%s", buff);
}

void send_fonction(const char *fonction_key)
{
    int size = snprintf(buff, BUFF_SIZE, "%s\n", fonction_key);
    UART_send_message(buff, size);
    debug(_DEBUG_, "envoie de la commande\n%s", buff);
}

