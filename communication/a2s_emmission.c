#include <stdarg.h> // pour le nombre variable d'argument
#include <stdio.h>

#include "../debug.h"

#include "a2s.h"
#include "a2s_emmission.h"

////////////////////////////////////////////////////////////////////////////////

void a2s_send_message(e_a2s commande, ...)
{
    va_list ap;

    va_start(ap, commande);

    // On envoie la commande
    printf("%s", a2s_keys[commande]);
    debug(_DEBUG_, "envoie [asser vers strategie] de la commande %s\n",
                a2s_keys[commande]);

    // On ajoute les argument éventuels
    // NB pour l'instant il n'y en a pas. La section suivante a été laissé pour
    // étendre facilement la fonction
    if (commande < A2S_VAL_SIZE) {
        // il y a un argument qui est un entier
        int d = va_arg(ap, int);
        printf("%d", d);
        debug(_DEBUG_, "avec pour argument : %d", d);
    }

    // On ajoute un retour chariot
    printf("\n");
    va_end(ap);
}
