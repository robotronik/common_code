#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inttypes.h"
#include "debug.h"
#include "protocole_uart.h"
#include "uart_emission.h"
char buffer_envoi[256];

void UART_putc(unsigned char c);

static void send_byte(uint8_t byte, uint8_t *crc) {
    switch (byte) {
        case '\\':
        case '\0':
            UART_putc('\\');
            *crc ^= '\\';

            // Dans tout les cas, l'étape suivante à lieu (pas de break
            // volontairement)
        default:
            UART_putc(byte);
            *crc ^= byte;
            break;
    }
}

void uart_trame_builder_init() {
    buffer_envoi[0] = '\0';
}

char* uart_trame_builder_get_string() {
    return buffer_envoi;
}

void uart_trame_builder_send_string() {
    uint8_t crc = 0;

    printf("MESSAGE ENVOYÉ :\n");
    int size_msg = strlen(buffer_envoi);

    for (int i = 0; i < size_msg; i++)
        send_byte(((uint8_t*)buffer_envoi)[i], &crc);

    printf("CRC :\n");
    send_byte(crc, &crc);

    printf("\\0 :\n");
    UART_putc('\0');

    printf("\n\n");
}


#define add_to_buffer_with_integer(string, value) sprintf(buffer_envoi, "%s%s%d\n", buffer_envoi, string, value)
#define add_to_buffer(string) sprintf(buffer_envoi, "%s%s\n", buffer_envoi, string)

void uart_trame_builder_append_coordonnees(int x, int y) {
    add_to_buffer_with_integer(UART_KEY_X, x);
    add_to_buffer_with_integer(UART_KEY_Y, y);
}
void uart_trame_builder_append_alphadelta(int alpha, int delta) {
    add_to_buffer_with_integer(UART_KEY_ALPHA, alpha);
    add_to_buffer_with_integer(UART_KEY_DELTA, delta);
}
void uart_trame_builder_append_theta(int theta) {
    add_to_buffer_with_integer(UART_KEY_THETA, theta);
}


void uart_trame_builder_append_nouveau_point_dans_chemin()   { add_to_buffer(UART_KEY_POINT_DANS_CHEMIN);   }
void uart_trame_builder_append_execute_le_chemin()           { add_to_buffer(UART_KEY_EXECUTE_LE_CHEMIN);   }

void uart_trame_builder_append_mouvement_xy_absolu()         { add_to_buffer(UART_KEY_MV_XY_ABSOLU);        }
void uart_trame_builder_append_mouvement_xy_relatif()        { add_to_buffer(UART_KEY_MV_XY_RELATIF);       }

void uart_trame_builder_append_mouvement_alphadelta()        { add_to_buffer(UART_KEY_MV_ALPHADELTA);       }
void uart_trame_builder_append_mouvement_alpha()             { add_to_buffer(UART_KEY_MV_ALPHA);            }
void uart_trame_builder_append_mouvement_delta()             { add_to_buffer(UART_KEY_MV_DELTA);            }
void uart_trame_builder_append_mouvement_theta()             { add_to_buffer(UART_KEY_MV_THETA);            }

void uart_trame_builder_append_mode_tendu()                  { add_to_buffer(UART_KEY_MODE_TENDU);          }
void uart_trame_builder_append_mode_courbe()                 { add_to_buffer(UART_KEY_MODE_COURBE);         }

void uart_trame_builder_append_stop_normal()                 { add_to_buffer(UART_KEY_STOP_NORMAL);         }
void uart_trame_builder_append_stop_urgence()                { add_to_buffer(UART_KEY_STOP_URGENCE);        }
