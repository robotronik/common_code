#include "../debug.h"

#include "../../asservissement/match.h"
#include "../../asservissement/odometrie.h"
#include "../../asservissement/trajectoire.h"

#include "s2a.h"
#include "s2a_reception.h"
#include "text_reception.h"
#include "text_reception.h"

/**
 * La liste des états de la machine à état en réception
 * \see s2a_state_name pour plus de détails
 */
typedef enum {
    S2A_WAIT_X,
    S2A_WAIT_Y,
    S2A_WAIT_ALPHA,
    S2A_WAIT_DELTA,
    S2A_WAIT_THETA,
    S2A_WAIT_KEY,
    S2A_WAIT_NEW_LINE,
    S2A_STATE_SIZE,
} e_s2a_state;

/**
 * Fonction d'aide appelé avec la commande `?`
 */
void s2a_help();

static char *s2a_keys_help[S2A_SIZE] = {
    [S2A_KEY_X]            = "coordonnées absolu en cm",
    [S2A_KEY_Y]            = "coordonnées absolu en cm",
    [S2A_KEY_ALPHA]        = "angle relatif en ???? degré? milidegré?",
    [S2A_KEY_DELTA]        = "distance relative en cm",
    [S2A_KEY_THETA]        = "angle absolu en ???? degré? milidegré?",

    [S2A_CMD_QUIT]         = "quitter la simulation",
    [S2A_CMD_HELP]         = "affiche l'aide",

    [S2A_FCT_ALPHA_DELTA]  = "set_trajectoire_alpha_delta(alpha, delta)",
    [S2A_FCT_XY_RELATIF]   = "set_trajectoire_xy_relatif(x,y)",
    [S2A_FCT_XY_ABSOLU]    = "set_trajectoire_xy_absolu(x,y)",
    [S2A_FCT_THETA]        = "set_trajectoire_theta(theta)",
    [S2A_FCT_ADD]          = "Ajoute les points x et y dans le prochain chemin",
    [S2A_FCT_CLEAR]        = "Efface le chemin en cours de construction",
    [S2A_FCT_CHEMIN]       = "Envoie le chemin précédemment construit",
    [S2A_FCT_UPDATE]       = "met à jour les variables du protocole de simulation "
            "pour qu'elles correspondent à celle utilisées par l'assert",
    [S2A_FCT_MODE_TENDU]   = "déplacement en mode tendu",
    [S2A_FCT_MODE_COURBE]  = "déplacement en mode courbe",
};

/**
 * Efface le chemin en cours de création
 */
void efface_chemin(s_liste *chemin);

/**
 * Ajoute un point dans le chemin en cours de création
 */
void add_point(int x, int y, s_liste *chemin);

////////////////////////////////////////////////////////////////////////////////

void s2a_help()
{
    info("\n-------------------------------\n");
    info("Liste des commandes supportées:\n\n");

    for (int i = 0; i < S2A_SIZE; i++) {
        if (i == 0) {
            info("    VARIABLES: attends un entier (pouvant être précédé d'un `-`) en paramêtre\n");
        } else if (i == S2A_VAL_MAX_INDEX + 1) {
            info("    COMMANDES: pas de paramètre\n");
        } else if (i == S2A_FCT_MAX_INDEX + 1) {
            info("    FONCTIONs: utilise les variables passé précédemment comme argument\n");
        }

        info("%-20s%s\n", s2a_keys[i], s2a_keys_help[i]);

        // séparation des partie
        if ((i == S2A_VAL_MAX_INDEX) || (i == S2A_CMD_MAX_INDEX)) {
            info("\n");
        }
    }

    info("\nRemarque: les espaces et les tabulations sont ignorées dans"
                "les commandes.\n");
    info("-------------------------------\n\n");
}

////////////////////////////////////////////////////////////////////////////////

void s2a_lecture_message(char current_char)
{
    static bool to_search[S2A_SIZE] = {true, true, true, true, true,
                                       true, true, true, true, true,
                                       true, true, true, true, true};
    static struct search_key_t sk = {
        0,
        S2A_SIZE,
        s2a_keys,
        to_search
    };
    static e_s2a_state current_state = S2A_WAIT_KEY;

    // Variables du programme en cour de réception
    static int x = 0, y = 0, alpha = 0, delta = 0, theta = 0;
    static s_liste chemin = { .taille = 0 };

    ////////////////////

    prepare_current_char(&current_char);
    debug(_DEBUG_, "\n\ncharactère lu : %c\n", current_char);

    switch (current_state) {

        ////////////////////

        case S2A_WAIT_KEY: {

            ////////////////////

            debug(_DEBUG_, "attente d'une fonction ou d'une commande\n");

            if(is_whitespace(current_char)) {
                debug(_DEBUG_, "espace ignoré dans la clé\n");
                break;
            }

            int ret = search_key(current_char, &sk);

            ////////////////////

            if (ret >= S2A_SIZE) {
                debug(_ERROR_, "ERREUR, clé inconnu: %d\n", ret);
            }
            else if (ret == -1) {
                // erreur, on attend la fin du message courant
                debug(_ERROR_, "ERREUR, clé non trouvé\n");
                s2a_help();
                if (is_end(current_char)) {
                    current_state = S2A_WAIT_KEY;
                } else {
                    current_state = S2A_WAIT_NEW_LINE;
                }
            }

            ////////////////////

            // On a fini de recevoir la clé
            if (ret >= 0) {
                reset_search(&sk);
                debug(_DEBUG_, "CLÉ TROUVÉ : %s\n", s2a_keys[ret]);

                switch (ret) {
                    case S2A_KEY_X:
                        x = 0;
                        current_state = S2A_WAIT_X;
                        break;

                    case S2A_KEY_Y:
                        y = 0;
                        current_state = S2A_WAIT_Y;
                        break;

                    case S2A_KEY_ALPHA:
                        alpha = 0;
                        current_state = S2A_WAIT_ALPHA;
                        break;

                    case S2A_KEY_DELTA:
                        delta = 0;
                        current_state = S2A_WAIT_DELTA;
                        break;

                    case S2A_KEY_THETA:
                        theta = 0;
                        current_state = S2A_WAIT_THETA;
                        break;

                    case S2A_CMD_QUIT:
                        // fin du match
                        // NB: ce cas n'est normalement pas à être géré par l'assert
                        debug(_DEBUG_, "FIN DU MATCH\n");
                        match_set_etat(MATCH_FIN);
                        break;

                    case S2A_CMD_HELP:
                        s2a_help();
                        current_state = S2A_WAIT_NEW_LINE;
                        break;

                    case S2A_FCT_ALPHA_DELTA:
                        debug(_DEBUG_, "set_trajectoire_alpha_delta(%d, %d);\n", alpha, delta);
                        set_trajectoire_alpha_delta(alpha, delta);
                        current_state = S2A_WAIT_NEW_LINE;
                        break;

                    case S2A_FCT_XY_RELATIF:
                        debug(_DEBUG_, "set_trajectoire_xy_relatif(%d, %d);\n", x, y);
                        set_trajectoire_xy_relatif(x, y);
                        current_state = S2A_WAIT_NEW_LINE;
                        break;

                    case S2A_FCT_XY_ABSOLU:
                        debug(_DEBUG_, "set_trajectoire_xy_absolu(%d, %d);\n", x, y);
                        set_trajectoire_xy_absolu(x, y);
                        current_state = S2A_WAIT_NEW_LINE;
                        break;

                    case S2A_FCT_THETA:
                        debug(_DEBUG_, "set_trajectoire_theta(%d);\n", theta);
                        set_trajectoire_theta(theta);
                        current_state = S2A_WAIT_NEW_LINE;
                        break;

                    case S2A_FCT_ADD:
                        add_point(x, y, &chemin);
                        current_state = S2A_WAIT_NEW_LINE;
                        break;

                    case S2A_FCT_CLEAR:
                        efface_chemin(&chemin);
                        current_state = S2A_WAIT_NEW_LINE;
                        break;

                    case S2A_FCT_CHEMIN:
                        add_point(x, y, &chemin);
                        debug(_DEBUG_, "Envoie du chemin\n");
                        for (int i = 0; i < chemin.taille; i++) {
                            debug(_DEBUG_, "	%d, %d\n", chemin.point[i].x, chemin.point[i].y);
                        }
                        set_trajectoire_chemin(chemin);
                        efface_chemin(&chemin);
                        current_state = S2A_WAIT_NEW_LINE;
                        break;

                    case S2A_FCT_UPDATE:
                        debug(_DEBUG_, "update()\n");
                        theta = get_theta_actuel();
                        x     = get_x_actuel();
                        y     = get_y_actuel();
                        alpha = get_alpha_actuel();
                        delta = get_delta_actuel();
                        debug(_DEBUG_, "Desormais, x = %d, y=%d, theta=%d, alpha=%d, delta=%d\n", x, y, theta, alpha, delta);
                        current_state = S2A_WAIT_NEW_LINE;
                        break;

                    case S2A_FCT_MODE_TENDU:
                        debug(_DEBUG_, "utilisation du mode tendu\n");
                        set_trajectoire_mode(tendu);
                        current_state = S2A_WAIT_NEW_LINE;
                        break;

                    case S2A_FCT_MODE_COURBE:
                        set_trajectoire_mode(courbe);
                        debug(_DEBUG_, "utilisation du mode courbe\n");
                        current_state = S2A_WAIT_NEW_LINE;
                        break;

                    default:
                        debug(_ERROR_, "ERREUR dans le programme de lecture des clées\n");
                        break;
                }
            }

            ////////////////////

            else {
                debug(_DEBUG_, "réception de la clé en cour\n");
            }

            ////////////////////

            break;
        }

        ////////////////////

        case S2A_WAIT_X:
            current_state = lecture_val(current_char, &x,
                    current_state, S2A_WAIT_KEY, S2A_WAIT_NEW_LINE);
            break;
        case S2A_WAIT_Y:
            current_state = lecture_val(current_char, &y,
                    current_state, S2A_WAIT_KEY, S2A_WAIT_NEW_LINE);
            break;
        case S2A_WAIT_ALPHA:
            current_state = lecture_val(current_char, &alpha,
                    current_state, S2A_WAIT_KEY, S2A_WAIT_NEW_LINE);
            break;
        case S2A_WAIT_DELTA:
            current_state = lecture_val(current_char, &delta,
                    current_state, S2A_WAIT_KEY, S2A_WAIT_NEW_LINE);
            break;
        case S2A_WAIT_THETA:
            current_state = lecture_val(current_char, &theta,
                    current_state, S2A_WAIT_KEY, S2A_WAIT_NEW_LINE);
            break;

        ////////////////////

        case S2A_WAIT_NEW_LINE: {
            // On attend la fin de la trame
            debug(_DEBUG_, "attente de la fin de la trame\n");

            if (is_end(current_char)) {
                // On se prépare à recevoir une nouvelle trame
                debug(_DEBUG_, "fin de trame trouvé\n");
                reset_search(&sk);
                current_state = S2A_WAIT_KEY;
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

void add_point(int x, int y, s_liste *chemin)
{
    debug(_DEBUG_, "ajout du point %d, %d\n", x, y);
    if (chemin->taille >= MAX_POSITIONS) {
        debug(_ERROR_, "\nAttention, le chemin est **trop long**. Point ignoré\n");
        return;
    }
    chemin->point[chemin->taille].x = x;
    chemin->point[chemin->taille].y = y;
    chemin->taille++;
}

void efface_chemin(s_liste *chemin)
{
    debug(_DEBUG_, "chemin effacé\n");
    chemin->taille = 0;
}
