#ifndef S2A_RECEPTION_H
#define S2A_RECEPTION_H

/**
 * REMARQUES GÉNÉRALES
 *    Ce fichiers sert d'interface pour la récéption concernant la communication
 *    de la stratégie vers l'asservissement
 *
 *    Par conséquent, il doit être inclus dans les fichiers **asservissement**
 *    uniquement.
 */

#include "s2a.h" // contient la définition de l'enum e_s2a

/**
 * Analyse le texte en provenance de la stratégie, et exécute les commandes
 * liées associé de l'asservissement
 *
 * \note Fonction est à exécuter lors des interruption en provenance de l'uart
 */
void s2a_lecture_message(char current_char);

#endif /* S2A_RECEPTION_H */
