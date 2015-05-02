#ifndef INTERNAL_RECEPTION_H
#define INTERNAL_RECEPTION_H

/**
 * REMARQUES GÉNÉRALES
 *    Ce fichiers contient des définition utilisé en interne par la réception.
 *
 *    Par conséquent, il doit être inclus lors de la compilation de
 *    **asservissement** et de la **stratégie**, mais ne doit pas être utilisé
 *    en dehors de s2a_reception.cet a2s_reception.c
 */

#include <stdbool.h>

/**
 * Traitement à effectuer l'analyse d'un caractère lors de la reception
 *
 * Pour simplifier le traitement, le protocole n'est pas sensible à la casse
 */
void prepare_current_char(char *current_char);

/**
 * Renvoie `true` si `c` est un caractère blanc (espace ou tab)
 */
bool is_whitespace(char c);

#endif /* INTERNAL_RECEPTION_H */
