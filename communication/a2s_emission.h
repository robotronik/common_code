#ifndef A2S_emission_H
#define A2S_emission_H

/**
 * REMARQUES GÉNÉRALES
 *    Ce fichiers sert d'interface pour l'emission concernant la communication
 *    de l'asservissement vers la stratégie.
 *
 *    Par conséquent, il doit être inclus dans les fichiers **asservissement**
 *    uniquement.
 */

#include "a2s.h" // contient la définition de l'enum e_a2s

/**
 * Envoie la commande `commande` suivit de son ou ses éventuels arguments et
 * d'un retour à la ligne
 *
 * Pour la liste des arguments possible, référer vous à l'enum e_a2s
 *
 * exemple:
 *
 * send_message(A2S_DONE);
 *
 */
void a2s_send_message(e_a2s commande, ...);


#endif /* A2S_emission_H */
