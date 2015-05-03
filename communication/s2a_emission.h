#ifndef S2A_EMMISSION_H
#define S2A_EMMISSION_H

/**
 * REMARQUES GÉNÉRALES
 *    Ce fichiers sert d'interface pour l'emmission concernant la communication
 *    de l'asservissement vers la stratégie.
 *
 *    Par conséquent, il doit être inclus dans les fichiers **asservissement**
 *    uniquement.
 */

#include "s2a.h" // contient la définition de l'enum e_s2a

/**
 * Envoie la commande `commande` suivit de son ou ses éventuels arguments et
 * d'un retour à la ligne
 *
 * Pour la liste des arguments possible, référer vous à l'enum e_s2a
 *
 * exemple:
 *
 * send_message(S2A_DONE);
 *
 */
void s2a_send_message(e_s2a commande, ...);


#endif /* S2A_EMMISSION_H */
