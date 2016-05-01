#ifndef COMMUNICATION_KEYS_H
#define COMMUNICATION_KEYS_H

typedef void (*callback_t) (void);

typedef enum {
    //// Ces fonctions attendent une valeur entière
    VAL_X,
    VAL_Y,
    VAL_ALPHA,
    VAL_DELTA,
    VAL_THETA,

    VAL_KP_DELTA,   // mise à jour du coeff KP pour le PID de delta
    VAL_KD_DELTA,   // mise à jour du coeff KD pour le PID de delta
    VAL_KP_ALPHA,   // mise à jour du coeff KP pour le PID de alpha
    VAL_KD_ALPHA,   // mise à jour du coeff KD pour le PID de alpha

    VAL_MAX_INDEX = VAL_KD_ALPHA,   // Avant, on a un arg. Après, pas d'args.

    //// Ces commandes ne demandent pas d'argument

    // Fonctions : à appeler après avoir envoyé des valeurs pour "confirmer"
    FCT_ALPHA_DELTA,// new_alpha_delta(alpha, delta);
    FCT_XY_RELATIF, // new_xy_relatif(x,y);
    FCT_XY_ABSOLU,  // new_xy_absolu(x,y);
    FCT_THETA,      // new_theta(theta);

    FCT_ADD,        // Ajoute les points x et y dans le prochain chemin
    FCT_CLEAR,      // Efface le chemin en cours de construction
    FCT_CHEMIN,     // set_trajectoire_chemin(chemin);

    FCT_MODE_TENDU, // set_trajectoire_mode(tendu);
    FCT_MODE_COURBE,// set_trajectoire_mode(courbe);

    FCT_SET_POS,    // change la valeure actuelle de x,y et theta
    FCT_SET_PID,    // change les valeurs des PID


    CMD_DONE,       // d    : l'asservissement a fini le trajet en cours
    CMD_GET_POS,    //      : demande x,y et theta actuel
    CMD_SEND_POS,   // p    : fin de réception de x,y,et theta
    CMD_QUIT,       // q    : quite la simulation
    CMD_HELP,       // ?    : affiche l'aide

    CMD_LOCK,       // On met en pause l'asservissement
    CMD_UNLOCK,

    CMD_STOP,           // arrêt
    CMD_EMERGENCY_STOP, // arrêt d'urgence


    KEYS_SIZE,
    CMD_MAX_INDEX = KEYS_SIZE-1,
} e_communication_keys;

extern char *keys[KEYS_SIZE];
extern char *keys_help[KEYS_SIZE];


#endif /* COMMUNICATION_KEYS_H */
