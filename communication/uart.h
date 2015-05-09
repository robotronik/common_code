#ifndef UART_H
#define UART_H

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
 * Lit un message en entrée
 * \return le nombre d'octets lus
 */
int UART_getc(unsigned char *byte);

#endif /* UART_H */
