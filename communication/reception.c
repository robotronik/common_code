#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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
    for (int i = 0; i < sk->nb_keys; i++)
        sk->to_search[i] = true;
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

int lecture_val(char c, int *val, bool *is_neg_number, bool *first_char) {

    // Lecture d'un entier
    debug(_VERBOSE_, "lecture entier\n");

    if (*first_char) {
        *val = 0;
        *is_neg_number = false;
        *first_char = false;

        // On regarde si le nombre est négatif (ce doit être le premier caractère)
        if (c == '-') {
            debug(_DEBUG_, "Le nombre est négatif\n");
            *is_neg_number = true;
            return WAIT_VALUE;
        }
    }


    if (is_end(c)) {
        // Réception terminée
        if (*is_neg_number)
            *val = -*val;

        debug(_DEBUG_, "réception terminée\n");
        debug(_DEBUG_, "valeur: %d\n", *val);

        // On se prépare à recevoir une nouvelle trame
        *first_char = true;
        return WAIT_KEY;
    }


    if ((c < '0') || (c > '9')) {
        debug(_ERROR_, "erreur, %c n'est pas un nombre\n", c);
        return WAIT_NEW_LINE;
    }
    if (*val > INT_MAX/10) {
        debug(_ERROR_, "overflow lors de la lecture d'un nombre\n");
        return WAIT_NEW_LINE;
    }


    *val = (*val * 10) + (c - '0');

    debug(_VERBOSE_, "réception en cours\n");
    debug(_VERBOSE_, "valeur en cours de lecture: %d\n", *val);
    return WAIT_VALUE;
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
