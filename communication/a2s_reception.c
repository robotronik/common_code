#include "../debug.h"

#include "a2s.h"
#include "a2s_reception.h"
#include "internal_reception.h"
#include "text_reception.h"

/**
 * La liste des états de la machine à état en réception
 * \see a2s_state_name pour plus de détails
 */
typedef enum {
    A2S_WAIT_KEY,
    A2S_WAIT_NEW_LINE,
} e_a2s_state;

/**
 * Fonction d'aide appelé avec la commande `?`
 */
void a2s_help();

static char *a2s_keys_help[A2S_SIZE] = {
    [A2S_CMD_DONE]         = "L'asservissement à fini le trajet en cour",
    [A2S_CMD_QUIT]         = "quitter la simulation",
    [A2S_CMD_HELP]         = "affiche l'aide",
};

////////////////////////////////////////////////////////////////////////////////

void a2s_help()
{
    info("\n-------------------------------\n");
    info("Liste des commandes supportées:\n\n");

    for (int i = 0; i < A2S_SIZE; i++) {
        info("%-20s%s\n", a2s_keys[i], a2s_keys_help[i]);
    }

    info("\nRemarque: les espaces et les tabulations sont ignorées dans"
                "les commandes.\n");
    info("-------------------------------\n\n");
}

////////////////////////////////////////////////////////////////////////////////

void a2s_lecture_message(char current_char)
{
    static bool to_search[A2S_SIZE] = {true, true};
    static struct search_key_t sk = {
        0,
        A2S_SIZE,
        a2s_keys,
        to_search
    };
    static e_a2s_state current_state = A2S_WAIT_KEY;

    ////////////////////

    prepare_current_char(&current_char);
    debug(_DEBUG_, "\n\ncharactère lu : %c\n", current_char);

    switch (current_state) {

        ////////////////////

        case A2S_WAIT_KEY: {

            ////////////////////

            debug(_DEBUG_, "attente d'une fonction ou d'une commande\n");

            if(is_whitespace(current_char)) {
                debug(_DEBUG_, "espace ignoré dans la clé\n");
                break;
            }

            int ret = search_key(current_char, &sk);

            ////////////////////

            if (ret >= A2S_SIZE) {
                debug(_ERROR_, "ERREUR, clé inconnu: %d\n", ret);
            }
            else if (ret == -1) {
                // erreur, on attend la fin du message courant
                debug(_ERROR_, "ERREUR, clé non trouvé\n");
                a2s_help();
                if (is_end(current_char)) {
                    current_state = A2S_WAIT_KEY;
                } else {
                    current_state = A2S_WAIT_NEW_LINE;
                }
            }

            ////////////////////

            // On a fini de recevoir la clé
            if (ret >= 0) {
                debug(_DEBUG_, "CLÉ TROUVÉ : %s\n", a2s_keys[ret]);

                switch (ret) {
                    case A2S_CMD_DONE:
                        debug(_WARNING_, "TODO: appeler le code de la stratégie ici");
                        break;

                    case A2S_CMD_HELP:
                        a2s_help();
                        break;

                    case A2S_CMD_QUIT:
                        debug(_WARNING_, "TODO: fin de la simulation");
                        break;

                    default:
                        debug(_ERROR_, "ERREUR dans le programme de lecture des clées\n");
                        break;
                }
            }

            ////////////////////

            break;
        }

       ////////////////////

        case A2S_WAIT_NEW_LINE: {
            // On attend la fin de la trame
            debug(_DEBUG_, "attente de la fin de la trame\n");

            if (is_end(current_char)) {
                // On se prépare à recevoir une nouvelle trame
                debug(_DEBUG_, "fin de trame trouvé\n");
                reset_search(&sk);
                current_state = A2S_WAIT_KEY;
            }

            break;
        }

        ////////////////////

        default: {
            debug(_ERROR_, "Le message n'a pas été reconnu");
            break;
        }
    }
}

