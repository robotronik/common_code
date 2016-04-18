#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <debug.h>

#include "reception.h"


bool is_end(char c) {
    return (c == '\n')
        || (c == '\r')
        || (c == '\0');
}

bool is_whitespace(char c) {
    return (c == ' ')
        || (c == '\t');
}

void reset_search(struct search_key_t *sk)
{
    for (int i = 0; i < sk->nb_keys; i++) {
        sk->to_search[i] = true;
    };
    sk->index = 0;
}

int search_key(char c, struct search_key_t *sk)
{
    int ret = 0;

    if (is_end(c)) {
        debug(_VERBOSE_, "end of line\n");
        return -1;
    }

    for (int i = 0; i < sk->nb_keys; i++) {
        debug(_VERBOSE_, "%d : %d\n", i, sk->to_search[i]);
        if (sk->to_search[i]) {
            if (sk->keys[i][sk->index] != c) {
                debug(_VERBOSE_, "not to_search : %d\n", i);
                debug(_VERBOSE_, "c = %c, key = %c\n", c, sk->keys[i][sk->index]);
                sk->to_search[i] = false;
            } else {
                if (sk->keys[i][sk->index+1] == '\0') {
                    debug(_VERBOSE_, "found : %d\n", i);
                    return i;
                }
                // On comptabilise le nombre de clé encore valide
                ret ++;
            }
        }
    }

    sk->index++;
    return - ret - 1;
}

int read_string(char c, int *index, char *str, int size_str)
{
    if (is_end(c)) {
        debug(_VERBOSE_, "new_line\n");
        debug(_VERBOSE_, "return : %d\n", *index);
        return *index;
    }

    if (*index >= size_str) {
        debug(_VERBOSE_, "buffer overflow\n");
        return -1;
    }

    debug(_VERBOSE_, "read_string : %c\n", c);
    str[*index] = c;
    *index = *index + 1;
    debug(_VERBOSE_, "index : %d\n", *index);
    return 0;
}

int read_unsigned(char c, int *val)
{
    if (is_end(c)) {
        debug(_VERBOSE_, "new_line\n");
        return 1;
    }

    // On s'assure qu'on a reçu un nombre
    if ((c < '0') || (c > '9')) {
        debug(_ERROR_, "erreur, %c n'est pas un nombre\n", c);
        return -2;
    }

    int pre_val = *val;
    *val *= 10;
    *val += c - '0';

    // overflow
    if (*val < pre_val) {
        debug(_ERROR_, "overflow lors de la lecture d'un nombre");
        return -1;
    }

    return 0;
}



int lecture_val(char c, int *val, int state_lecture, int state_found, int state_error)
{
    static bool is_neg_number;
    static bool first_char = true;

    // Lecture d'un entier
    debug(_VERBOSE_, "lecture entier\n");

    if(is_whitespace(c)) {
        debug(_DEBUG_, "espace ignoré durant la lecture d'une valeur\n");
        return state_lecture;
    }

    if (first_char) {
        *val = 0;
        is_neg_number = false;
        first_char = false;

        // On regarde si le nombre est négatif (ce doit être le premier caractère)
        if (c == '-') {
            debug(_DEBUG_, "Le nombre est négatif\n");
            is_neg_number = true;
            return state_lecture;
        }
    }

    int ret = read_unsigned(c, val);
    debug(_VERBOSE_, "valeur en cours de lecture: %d\n", *val);

    // la récéption n'est pas fini, on reste dans le même état
    if (ret == 0) {
        debug(_VERBOSE_, "reception en cours\n");
        return state_lecture;
    }

    // reception terminée
    else if (ret > 0) {
        if (is_neg_number) {
            *val = -*val;
        }
        debug(_DEBUG_, "reception terminée\n");
        debug(_DEBUG_, "valeur: %d\n", *val);

        // On se prépare à recevoir une nouvelle trame
        first_char = true;
        is_neg_number = false;
        return state_found;
    }

    // il y a eu des erreurs de reception
    else {
        return state_error;
    }
}


#include "keys.h"

void communication_help() {
    UART_send_message("\n-------------------------------\n");
    UART_send_message("Liste des commandes supportées:\n\n");

    char buff[100];

    for (int i = 0; i < KEYS_SIZE; i++) {
        if (i == 0)
            UART_send_message("\tVARIABLES: attends un entier (pouvant être précédé d'un `-`) en paramètre\n");
         else if (i == VAL_MAX_INDEX + 1)
            UART_send_message("\tCOMMANDES: pas de paramètres\n");


        sprintf(buff, "%-20s%s\n", keys[i], keys_help[i]);
        UART_send_message(buff);

        // séparation des partie
        if (i == VAL_MAX_INDEX) {
            UART_send_message("\n");
        }
    }

    UART_send_message("\nRemarque: les espaces et les tabulations sont ignorées dans"
                "les commandes.\n");
    UART_send_message("-------------------------------\n\n");
}
