#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <debug.h>
#include "lecture_reception.h"


void init_reception(Reception_object *values, callback_t *_callbacks) {
    if (values == 0 || _callbacks == 0)
        return;

    values->current_state = WAIT_KEY;
    values->sk.nb_keys = KEYS_SIZE;
    values->sk.keys=keys;
    values->sk.to_search=values->to_search;
    reset_search(&values->sk);

    values->received_value = 0;
    values->received_value_is_negative = false;
    values->received_value_first_char  = true;

    values->callbacks = _callbacks;
    _callbacks[CMD_HELP] = communication_help;
}


void lecture_message(char current_char, Reception_object *values) {
    // On ignore toujours les espaces
    if(is_whitespace(current_char))
        return;

    debug(_DEBUG_, "\n");
    debug(_DEBUG_, "Caractère lu : %c\n", current_char);

    switch (values->current_state) {
        case WAIT_KEY:  // On est en train de lire la clé
        {
            int ret = search_key(current_char, &(values->sk));

            if (ret == -1
             || ret >= KEYS_SIZE
             || ret == CMD_HELP) {
                // erreur, on attend la fin du message courant
                if (ret == -1)
                    debug(_ERROR_, "Erreur, clé non trouvée\n");

                if (ret >= KEYS_SIZE)
                    debug(_ERROR_, "Erreur, clé non trouvée : %d\n", ret);

                if (is_end(current_char))
                    values->current_state = WAIT_KEY;
                else
                    values->current_state = WAIT_NEW_LINE;
            }

            if (ret >= 0) {
                values->received_key = ret;
                debug(_DEBUG_, "Clé trouvée : %s\n", keys[values->received_key]);
                reset_search(&(values->sk));

                if (values->received_key <= VAL_MAX_INDEX) {
                    // Now we have to read the value
                    values->received_value = 0;
                    values->current_state = WAIT_VALUE;
                } else {
                    // We can call the callback !
                    if (values->callbacks[values->received_key])
                        values->callbacks[values->received_key]();
                    // Now we will wait for the end of the line
                    values->current_state = WAIT_NEW_LINE;
                }

            } else {
                debug(_DEBUG_, "Réception de la clé en cours\n");
            }
        }
            break;

        case WAIT_VALUE:    // On est en train de lire la valeur qui suit la clé
            values->current_state = lecture_val(current_char, &(values->received_value),
                        &(values->received_value_is_negative), &(values->received_value_first_char));
            if (values->current_state == WAIT_KEY) {
                // We can call the callback !
                if (values->callbacks[values->received_key])
                    values->callbacks[values->received_key]();
            }
            break;

        case WAIT_NEW_LINE: // On a fini de tout lire, on attend la fin
            // On attend la fin de la trame
            debug(_DEBUG_, "Attente de la fin de la trame\n");

            if (is_end(current_char)) {
                // On se prépare à recevoir une nouvelle trame
                debug(_DEBUG_, "Fin de trame trouvé\n");
                reset_search(&(values->sk));
                values->current_state = WAIT_KEY;
            }
            break;


        default:
            debug(_ERROR_, "Le message n'a pas été reconnu");
            break;
    }
}
