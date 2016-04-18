#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <debug.h>
#include "lecture_reception.h"
#include "reception.h"


typedef enum {
    WAIT_KEY,
    WAIT_VALUE,
    WAIT_NEW_LINE,
} e_a2s_state;

callback_t callbacks[KEYS_SIZE];

// Les valeurs reçues
e_communication_keys received_key;
int received_value = 0;


e_a2s_state current_state = WAIT_KEY;
bool to_search [KEYS_SIZE];
struct search_key_t sk = {
    0,
    KEYS_SIZE,
    keys,
    to_search
};

int init_reception(callback_t *_callbacks) {
    *callbacks = *_callbacks;

    reset_search(&sk);
    return 0;
}

int get_received_value() {
    return received_value;
}


void lecture_message(char current_char) {
    // On ignore toujours les espaces
    if(is_whitespace(current_char))
        return;

    debug(_DEBUG_, "\n\nCaractère lu : %c\n", current_char);

    switch (current_state) {
        case WAIT_KEY:
        {
            int ret = search_key(current_char, &sk);

            if (ret == -1
             || ret >= KEYS_SIZE
             || ret == CMD_HELP) {
                // erreur, on attend la fin du message courant
                if (ret == -1)
                    debug(_ERROR_, "Erreur, clé non trouvée\n");

                if (ret >= KEYS_SIZE)
                    debug(_ERROR_, "Erreur, clé inconnue: %d\n", ret);

                communication_help();
                if (is_end(current_char))
                    current_state = WAIT_KEY;
                else
                    current_state = WAIT_NEW_LINE;
            }

            if (ret >= 0) {
                reset_search(&sk);
                received_key = ret;
                debug(_DEBUG_, "Clé trouvée : %s\n", keys[received_key]);

                if (received_key <= VAL_MAX_INDEX) {
                    // Now we have to read the value
                    received_value = 0;
                    current_state = WAIT_VALUE;
                } else {
                    // We can call the callback !
                    if (callbacks[received_key])
                        callbacks[received_key]();
                    // Now we will wait for the end of the line
                    current_state = WAIT_NEW_LINE;
                }

            } else {
                debug(_DEBUG_, "Réception de la clé en cours\n");
            }
        }
            break;

        case WAIT_VALUE:
            current_state = lecture_val(current_char, &received_value,
                    current_state, WAIT_KEY, WAIT_NEW_LINE);
            break;

        case WAIT_NEW_LINE:
        {
            // On attend la fin de la trame
            debug(_DEBUG_, "Attente de la fin de la trame\n");

            if (is_end(current_char)) {
                // On se prépare à recevoir une nouvelle trame
                debug(_DEBUG_, "Fin de trame trouvé\n");
                reset_search(&sk);
                current_state = WAIT_KEY;
            }
        }
            break;


        default:
        {
            debug(_ERROR_, "Le message n'a pas été reconnu");
        }
            break;
    }


}
