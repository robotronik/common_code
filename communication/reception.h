#ifndef COMMUNICATION_RECEPTION_H
#define COMMUNICATION_RECEPTION_H

#include <stdbool.h>

/**
 * REMARQUES GÉNÉRALES
 *    Ce fichiers contient des définition utilisé en interne par la réception.
 *
 *    Par conséquent, il doit être inclus lors de la compilation de
 *    **asservissement** et de la **stratégie**, mais ne doit pas être utilisé
 *    en dehors de s2a_reception.cet a2s_reception.c
 *
 * La gestion des espaces blancs (espace, tabs, …) est laissée à l'utilisateur.
 */

/** Structure servant contenant les clés que l'on peut trouver lors de la
 * reception de texte
 */
struct search_key_t {
    int index;             ///< index du prochain caractère à lire
    int nb_keys;           ///< taille de keys[] en nombre d'élément
    char **keys;           ///< tableaux contenant les clés à rechercher
    bool *to_search;       ///< il faut chercher keys[i] si to_search[i] == true
};


typedef enum {
    WAIT_KEY,
    WAIT_VALUE,
    WAIT_NEW_LINE,
} e_a2s_state;

// Retourne true si [c] est un caractère de fin (\0, \r ou \n)
bool is_end(char c);
// Retourne true si [c] est un caractère blanc (espace ou tab)
bool is_whitespace(char c);

// Prépare le caractère à gérer (tolower)
void prepare_current_char(char *current_char);


/** prépare [sk] pour une nouvelle recherche
 */
void reset_search(struct search_key_t *sk);

/** Cherche si [c] est une clé valide dans [sk]
 *
 * Le caractère [c] va être comparé au caractère à l'indice [sk.index] des
 * chaines [sk.keys], à condition que la chaine soit à rechercher (ce qui
 * équivaut à [sk.keys.to_search == true).
 *
 * Si [c] est un caractère de fin de séquence (\0, \n et \r), alors l'indice de
 * la première chaine à rechercher est retourné.
 *
 * Sinon, [keys.to_search] va être mis à jour, et -(le nombre de chaine encore
 * valide + 1) est retourné. Par conséquent, -1 signifie qu'il n'y a plus
 * aucune chaine valide.
 */
int search_key(char c, struct search_key_t *sk);


/*
 * Lecture d'une valeure
 *
 * \param c caractère en cours de réception
 * \param val valeur lu ou en cour de lecture (doit être mis à 0 avant la
 * première lecture).
 *
 * \return state_found si la reception est terminée
 * \return state_error en cas d'erreur
 * \return state_current sinon (réception non terminée).
 */
int lecture_val(char c, int *val, bool *is_neg_number, bool *first_char);


void communication_help();



#endif /* COMMUNICATION_RECEPTION_H */
