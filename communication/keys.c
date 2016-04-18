#include "keys.h"



char *keys[KEYS_SIZE] = {
    //// Ces fonctions attendent une valeur entière
    [VAL_X]             = "x=",
    [VAL_Y]             = "y=",
    [VAL_ALPHA]         = "alpha=",
    [VAL_DELTA]         = "delta=",
    [VAL_THETA]         = "theta=",

    [VAL_KP_DELTA]      = "KPd=",
    [VAL_KD_DELTA]      = "KDd=",
    [VAL_KP_ALPHA]      = "KPa=",
    [VAL_KD_ALPHA]      = "KDa=",

    // Avant, on a un arg. Après, pas d'args.

    //// Ces commandes ne demandent pas d'argument

    // Fonctions : à appeler après avoir envoyé des valeurs pour "confirmer"
    [FCT_ALPHA_DELTA]   = "alpha_delta()",
    [FCT_XY_RELATIF]    = "xy_relatif()",
    [FCT_XY_ABSOLU]     = "xy_absolu()",
    [FCT_THETA]         = "theta()",

    [FCT_ADD]           = "add()",
    [FCT_CLEAR]         = "clear()",
    [FCT_CHEMIN]        = "chemin()",

    [FCT_MODE_TENDU]    = "mode(tendu)",
    [FCT_MODE_COURBE]   = "mode(courbe)",

    [FCT_SET_POS]       = "set_pos()",
    [FCT_SET_PID]       = "change_pid()",


    [CMD_DONE]          = "done",
    [CMD_GET_POS]       = "get_pos()",
    [CMD_SEND_POS]      = "pos_sent",
    [CMD_QUIT]          = "quit",
    [CMD_HELP]          = "?",

    [CMD_STOP]          = "stop",
    [CMD_EMERGENCY_STOP]= "estop",

};

char *keys_help[KEYS_SIZE] = {
    //// Ces fonctions attendent une valeur entière
    [VAL_X]             = "coordonnées absolu en cm",
    [VAL_Y]             = "coordonnées absolu en cm",
    [VAL_ALPHA]         = "angle relatif en miliradiants",
    [VAL_DELTA]         = "distance relative en cm",
    [VAL_THETA]         = "angle absolu en miliradiants",

    [VAL_KP_DELTA]      = "coefficient KP du PID pour delta",
    [VAL_KD_DELTA]      = "coefficient KD du PID pour delta",
    [VAL_KP_ALPHA]      = "coefficient KP du PID pour alpha",
    [VAL_KD_ALPHA]      = "coefficient KD du PID pour alpha",

    // Avant, on a un arg. Après, pas d'args.

    //// Ces commandes ne demandent pas d'argument

    // Fonctions : à appeler après avoir envoyé des valeurs pour "confirmer"
    [FCT_ALPHA_DELTA]   = "set_trajectoire_alpha_delta(alpha, delta)",
    [FCT_XY_RELATIF]    = "set_trajectoire_xy_relatif(x,y)",
    [FCT_XY_ABSOLU]     = "set_trajectoire_xy_absolu(x,y)",
    [FCT_THETA]         = "set_trajectoire_theta(theta)",

    [FCT_ADD]           = "Ajoute les points x et y dans le prochain chemin",
    [FCT_CLEAR]         = "Efface le chemin en cours de construction",
    [FCT_CHEMIN]        = "Envoie le chemin précédemment construit",

    [FCT_MODE_TENDU]    = "déplacement en mode tendu",
    [FCT_MODE_COURBE]   = "déplacement en mode courbe",

    [FCT_SET_POS]       = "défini la position du robot (x,y,theta)",
    [FCT_SET_PID]       = "défini les coefficients du PID d'asservissement",


    [CMD_DONE]          = "L'asservissement a fini le trajet en cours",
    [CMD_GET_POS]       = "demande x, y et theta actuel",
    [CMD_SEND_POS]      = "fin de réception de x, y et theta",
    [CMD_QUIT]          = "quitter la simulation",
    [CMD_HELP]          = "affiche l'aide",

    [CMD_STOP]          = "arrêt",
    [CMD_EMERGENCY_STOP]= "arrêt d'urgence",

};
