#ifndef A2S_H
#define A2S_H

/**
 * REMARQUES GÉNÉRALES
 *    Ce fichiers sert d'interface à la partie commune concernant la
 *    communication de l'asservissement vers la stratégie.
 *
 *    Par conséquent, il doit être inclus dans les fichiers **asservissement**
 *    et **stratégie**.
 */

typedef enum {
    // valeures: la fonction a2s_send_message() attend un entier en argument
    A2S_VAL_X,
    A2S_VAL_Y,
    A2S_VAL_THETA,
    // commandes: pas d'argument
    A2S_CMD_DONE,       // d         : l'asservissement à fini le trajet en cour
    A2S_CMD_SEND_POS,   // p         : fin de reception de x,y,et theta
    A2S_CMD_QUIT,       // q         : quite la simulation
    A2S_CMD_HELP,       // ?         : affiche l'aide
    // fonction: utilise les valeurs précédement envoyé, donc pas d'argument dans la
    // fonction a2s_send_message()
    A2S_SIZE,
    A2S_VAL_MAX_INDEX = A2S_VAL_THETA,
} e_a2s;


////////////////////////////////////////////////////////////////////////////////


/**
 * USAGE INTERNE UNIQUEMENT
 *    La suite de ce fichier contient des définitions commune à la communication
 *    de l'asservissement vers la stratégie, utilisé en interne dans le
 *    protocole de communication.
 *
 *    Par conséquent, il doit être inclus lors de la compilation de
 *    **asservissement** et de la **stratégie**, mais ne doit pas être utilisé
 *    en dehors de a2s_emission.c et a2s_reception.c
 */

/**
 * Le tableau a2s_keys contient la liste de toutes les commandes pouvant
 * transiter de l'asservissement vers la stratégie
 *
 * Ce tableau est indéxé avec l'ennumération e_a2s.
 *
 * exemple:
 *     printf("done");
 * sera totalement équivalent à
 *     printf(a2s_keys[A2S_DONE]);
 * ou mieu, à
 *     send_commande(A2S_DONE);
 * avec pour avantage que si la chaine correspondant à DONE change, cela sera
 * répercutté automatiquement
 *
 * \warning Ce tableau ne doit pas être modifié lors de l'exécution du programme
 * \see text_emission.h
 */
extern char *a2s_keys[A2S_SIZE];


#endif /* A2S_H */
