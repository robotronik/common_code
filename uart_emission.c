#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../stm32f407/headers/main.h"
#include "debug.h"
#include "protocole_uart.h"
#include "uart_emission.h"
char buffer_envoi[40];

void UART_send_message(char*);

void uart_trame_builder_init() {
    buffer_envoi[0] = '\0';
}

void uart_trame_builder_send_string() {
    UART_send_message(buffer_envoi);
}

#define add_to_buffer_with_int(string, value) sprintf(buffer_envoi, "%s%s%d\n", buffer_envoi, string, value)
#define add_to_buffer(string) sprintf(buffer_envoi, "%s%s\n", buffer_envoi, string)

void uart_trame_builder_append_coordonnees(int x, int y) {
    add_to_buffer_with_int(UART_KEY_X, x);
    add_to_buffer_with_int(UART_KEY_Y, y);
}
void uart_trame_builder_append_alphadelta(int alpha, int delta) {
    add_to_buffer_with_int(UART_KEY_ALPHA, alpha);
    add_to_buffer_with_int(UART_KEY_DELTA, delta);
}
void uart_trame_builder_append_theta(int theta)              { add_to_buffer_with_int(UART_KEY_THETA,theta);}

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
