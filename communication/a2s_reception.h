#ifndef A2S_RECEPTION_H
#define A2S_RECEPTION_H

/**
 * REMARQUES GÉNÉRALES
 *    Ce fichiers sert d'interface pour la récéption concernant la communication
 *    de l'asservissement vers la stratégie.
 *
 *    Par conséquent, il doit être inclus dans les fichiers **stratégie**
 *    uniquement.
 */

#include "a2s.h" // contient la définition de l'enum e_a2s

/** Analyse le texte en provenance de l'asservissement, et exécute les commandes
 * liées à la stratégie.
 *
 * \note Fonction est à exécuter lors des interruption en provenance de l'uart
 */
void a2s_lecture_message(char current_char);

#endif /* A2S_RECEPTION_H */
