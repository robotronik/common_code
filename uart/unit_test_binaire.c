#include "inttypes.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

#include "reception.h"
#include "emission.h"
#include "../common_code/common.h"

/* Test unitaire permettant de valider le protocole binaire */

int main(void)
{
    struct my_data_t {
        int8_t type;
        struct {
            uint8_t x,y;
        } point[3];
    };

    extern struct g_communication_t g_communication;

    uint8_t msg1[] = "ab:cd:eA";
    uint8_t msg2[] = "test\\xy\0";
    struct my_data_t msg3 = {3, {{1,2},{10,20},{33,44}}};

    uint8_t buf1[sizeof(msg1)];
    uint8_t buf2[sizeof(msg2)];
    struct my_data_t buf3;

    // Pour les tests j'envoie tout les caractères prélablement
    uart_send_msg(msg1,  sizeof(msg1));
    uart_send_msg(msg2,  sizeof(msg2));
    uart_send_msg(&msg3, sizeof(msg3));
    debug("msg envoyé:\n");
    extern uint8_t buf[50];
    for (unsigned i = 0; i < sizeof(buf); i++) {
        debug_byte(buf[i]);
    }

    debug("\n");
    debug("FIN TRANSMISSION\n");
    debug("\n");

    // Dans un premier temps on utilise buf1
    g_communication.data = buf1;
    g_communication.data_size = sizeof(buf1);
    g_communication.state = PRET;

    // La trame transmise sera donc (en hexa) : 08 61 62 3A 64 65 3A 66 67 0F

    // On attend de recevoir des données
    while(g_communication.state != RECU) {
        lire_uart();
    }

    // On vérifie que le message est bien reçu
    debug("\n");
    debug("MSG1 %.*s\n", sizeof(msg1), msg1);
    debug("BUF1 %.*s\n", sizeof(buf1), buf1);
    for (unsigned i = 0; i < sizeof(buf1); i++) {
        debug_byte(buf1[i]);
    }
    debug("\n");
    /*assert(!strncmp(msg1, buf1, sizeof(msg1 - 1)));*/

    // buf1 est plein, maintenant, on utilise buf2
    g_communication.data = buf2;
    g_communication.data_size = sizeof(buf2);
    g_communication.state = PRET;

    lire_uart();
    lire_uart();
    lire_uart();
    lire_uart();

    // On peut faire un travail sur buf1, pendant que buf2 se remplis…
    debug("\n");
    debug("lecture de buf1 pendant que l'on remplis buf2\n");
    debug("BUF1 %.*s\n", sizeof(buf1), buf1);
    debug("\n");

    // On attend de recevoir des données
    while(g_communication.state != RECU) {
        lire_uart();
    }

    debug("\n");
    debug("BUF2 %.*s\n", sizeof(buf2), buf2);
    debug("MSG2 %.*s\n", sizeof(msg2), msg2);
    debug("BUF2 %.*s\n", sizeof(buf2), buf2);
    for (unsigned i = 0; i < sizeof(buf2); i++) {
        debug_byte(buf2[i]);
    }
    debug("\n");

    // On transmet la dernière trame
    debug("sizeof(msg3) sizeof(buf3)%d\n", sizeof(msg3), sizeof(buf3));
    g_communication.data = (uint8_t*) &buf3;
    g_communication.data_size = sizeof(buf3);
    g_communication.state = PRET;

    while(g_communication.state != RECU) {
        lire_uart();
    }

    debug("\n");
    debug("BUF3 :\n");
    debug("type : %d\n", buf3.type);
    debug("point1 : %d %d\n", buf3.point[0].x, buf3.point[0].y);
    debug("point2 : %d %d\n", buf3.point[1].x, buf3.point[1].y);
    debug("point3 : %d %d\n", buf3.point[2].x, buf3.point[2].y);
}
