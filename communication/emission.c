#include <string.h>
#include <stdio.h>

#include <debug.h>

#include "emission.h"

////////////////////////////////////////////////////////////////////////////////

int send_val(char* buffer, const char *val_key, int value)
{
    int size = snprintf(buffer, BUFF_SIZE, "%s%d\n", val_key, value);
    debug(_DEBUG_, "envoi de la commande\n%s", buffer);
    return size;
}

int send_cmd(char* buffer, const char *com_key)
{
    int size = snprintf(buffer, BUFF_SIZE, "%s\n", com_key);
    debug(_DEBUG_, "envoi de la commande\n%s", buffer);
    return size;
}
