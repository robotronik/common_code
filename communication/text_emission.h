#ifndef TEXT_EMISSION_H
#define TEXT_EMISSION_H

/**
 * REMARQUES GÉNÉRALES
 *    Ce fichiers sert d'interface pour l'emmission
 *
 *    Par conséquent, il doit être inclus dans les tinaire **asservissement**
 *    et **stratégie**
 */

/**
 * Envoie la commande `val_key`, avec pour valeur `value` dans l'uart
 * Pour la liste des arguments possible, référer vous aux enum e_s2a et e_a2s
 *
 * \exemple send_val(a2s_keys[S2A_KEY_X], 2000);
 */
void send_val(const char *val_key, int value);

/**
 * Envoie la commande `commande_key` dans l'uart
 * Pour la liste des arguments possible, référer vous aux enum e_s2a et e_a2s
 *
 * \exemple send_val(a2s_keys[S2A_CMD_GET_POS]);
 */
void send_cmd(const char *commande_key);

/**
 * Envoie la commande `fonction_key` dans l'uart
 * Pour la liste des arguments possible, référer vous aux enum e_s2a et e_a2s
 * Le ou les arguments de la fonction doivent être envoyés avant à l'aide de la
 * fonction send_val()
 *
 * \exemple send_val(a2s_keys[S2A_FCT_THETA]);
 */
void send_fonction(const char *fonction_key);

#endif /* TEXT_EMISSION_H */
