#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../debug.h"

#include "text_reception.h"


bool is_end(char c)
{
    return (c == '\n') || (c == '\r') || (c == '\0');
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
                ret --;
            }
        }
    }

    sk->index++;
    return ret - 1;
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

int read_int(char c, int *val)
{
    if (is_end(c)) {
        debug(_VERBOSE_, "new_line\n");
        return 1;
    }

    // On s'assure qu'on a reçu un nombre
    if ((c < '0') || (c > '9')) {
        debug(_VERBOSE_, "erreur, %c n'est pas un nombre\n", c);
        return -2;
    }

    int pre_val = *val;
    *val *= 10;
    *val += c - '0';

    // overflow
    if (*val < pre_val) {
        debug(_VERBOSE_, "overflow");
        return -1;
    }

    return 0;
}

void prepare_current_char(char *current_char)
{
    // on ne tient pas compte de la casse
    *current_char = tolower(*current_char);
}

bool is_whitespace(char c)
{
    return (c == ' ') || (c == '\t');
}
