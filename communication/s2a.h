#ifndef S2A_H
#define S2A_H

/**
 * REMARQUES GÉNÉRALES
 *    Ce fichiers sert d'interface à la partie commune concernant la
 *    communication de l'asservissement vers la stratégie.
 *
 *    Par conséquent, il doit être inclus dans les fichiers **asservissement**
 *    et **stratégie**.
 */

typedef enum {
    // valeures: la fonction s2a_send_message() attend un entier en argument
    S2A_KEY_X,              // mise à jour de la variable x (coordonnée en cm)
    S2A_KEY_Y,              // mise à jour de la variable y (coordonnée en cm)
    S2A_KEY_ALPHA,          // mise à jour de la variable alpha (angle relatif en degré)
    S2A_KEY_DELTA,          // mise à jour de la variable delta (distance en cm)
    S2A_KEY_THETA,          // mise à jour de la variable theta (angle absolu en degré)
    // commandes: pas d'argument
    S2A_CMD_QUIT,           // quitte la simulation
    S2A_CMD_HELP,           // affiche l'aide
    // fonction: utilise les valeurs précédement envoyé, donc pas d'argument dans la
    // fonction s2a_send_message()
    S2A_FCT_ALPHA_DELTA,    // new_alpha_delta(alpha, delta);
    S2A_FCT_XY_RELATIF,     // new_xy_relatif(x,y);
    S2A_FCT_XY_ABSOLU,      // new_xy_absolu(x,y);
    S2A_FCT_THETA,          // new_theta(theta);

    S2A_FCT_ADD,            // Ajoute les points x et y dans le prochain chemin
    S2A_FCT_CLEAR,          // Efface le chemin en cours de construction
    S2A_FCT_CHEMIN,         // set_trajectoire_chemin(chemin);
    // NB: chemin() fait un appel à `add()`, set_trajectoire_chemin() puis `clear()`

    S2A_FCT_MODE_TENDU,     // set_trajectoire_mode(tendu);
    S2A_FCT_MODE_COURBE,    // set_trajectoire_mode(courbe);

    S2A_FCT_UPDATE,         // met à jour les variables utilisées dans la simulation

    // info
    S2A_SIZE,
    S2A_VAL_SIZE = S2A_KEY_THETA + 1
} e_s2a;


////////////////////////////////////////////////////////////////////////////////


/**
 * USAGE INTERNE UNIQUEMENT
 *    La suite de ce fichier contient des définitions commune à la communication
 *    de l'asservissement vers la stratégie, utilisé en interne dans le
 *    protocole de communication.
 *
 *    Par conséquent, il doit être inclus lors de la compilation de
 *    **asservissement** et de la **stratégie**, mais ne doit pas être utilisé
 *    en dehors de s2a_emission.c et s2a_reception.c
 */

/**
 * Le tableau s2a_keys contient la liste de toutes les commandes pouvant
 * transiter de l'asservissement vers la stratégie
 *
 * Ce tableau est indéxé avec l'ennumération e_s2a.
 *
 * exemple:
 *     printf("done");
 * sera totalement équivalent à
 *     s2a_send_message(s2a_keys[S2A_DONE]);
 * avec pour avantage que si la chaine correspondant à DONE change, cela sera
 * répercutté automatiquement
 *
 * \warning Ce tableau ne doit pas être modifié lors de l'exécution du programme
 */
extern char *s2a_keys[S2A_SIZE];


#endif /* S2A_H */
