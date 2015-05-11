#ifndef UART_H
#define UART_H

#include <stdbool.h>

/**
 * REMARQUES GÉNÉRALES
 *    Ce fichiers sert d'interface pour l'emmission
 *
 *    Par conséquent, il doit être inclus dans les tinaire **asservissement**
 *    et **stratégie**
 */

/**
 * Fonction d'envoie de message par l'uart
 *
 * \param msg Le message à envoyer
 * \param nb_char Le nombre de caractères dans msg
 */
void UART_send_message(char *msg, unsigned int nb_char);

/**
 * Intialisation de l'uart
 */
void UART_init();

/*
 * Essaye de lire un caractère.
 *
 * Si il y avait des caractère en attente, alors ce caractère est copié dans c,
 * et la fonction renvoie true.
 *
 * Sinon la fonction revoie false.
 *
 * \param c copie de la lettre reçu
 * \return true s'il y avait un caractère à lire
 */
int UART_getc(unsigned char *c);

#endif /* UART_H */
