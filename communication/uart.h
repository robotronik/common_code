#ifndef UART_H
#define UART_H

/**
 * Fonction d'envoie de message par l'uart
 *
 * \param msg Le message à envoyer
 * \param nb_char Le nombre de caractères dans msg
 */
void uart_send_message(char *msg, int nb_char);


#endif /* UART_H */
