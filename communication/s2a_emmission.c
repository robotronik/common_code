#include <stdarg.h> // pour le nombre variable d'argument

#include "../debug.h"

#include "s2a.h"
#include "s2a_emmission.h"
#include "text_emmission.h"

////////////////////////////////////////////////////////////////////////////////

/*
 * La fonction s2a_send_message() envoie du texte vers l'asservissement. La
 * suite de commande suivante
 *
 * x=300
 * y=400
 * xy_relatif() # le robot avance de 300 en x, 400 en y
 * xy_relatif() # le robot avance de nouveau de 300 en x, 400 en y
 *
 * est donc équivalente à:
 *
 * s2a_send_message(S2A_KEY_X, 300);
 * s2a_send_message(S2A_KEY_X, 300);
 * s2a_send_message(S2A_FCT_XY_RELATIF);
 * s2a_send_message(S2A_FCT_XY_RELATIF);
 */
void s2a_send_message(e_s2a commande, ...)
{
    va_list ap;

    va_start(ap, commande);

    // On envoie la commande
    send_text("%s", s2a_keys[commande]);
    debug(_DEBUG_, "envoie [asser vers strategie] de la commande %s\n",
                s2a_keys[commande]);

    // On ajoute les argument éventuels
    // NB pour l'instant il n'y en a pas. La section suivante a été laissé pour
    // étendre facilement la fonction
    if (commande < S2A_VAL_SIZE) {
        // il y a un argument qui est un entier
        int d = va_arg(ap, int);
        send_text("%d", d);
        debug(_DEBUG_, "avec pour argument : %d", d);
    }

    // On ajoute un retour chariot
    send_text("\n");
    va_end(ap);
}
