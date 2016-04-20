#ifndef COMMUNICATION_LECTURE_RECEPTION
#define COMMUNICATION_LECTURE_RECEPTION

#include "keys.h"

#include "reception.h"

typedef struct {
    e_a2s_state current_state;

    // Keys reception
    struct search_key_t sk;
    bool to_search [KEYS_SIZE];
    e_communication_keys received_key;

    // Values reception
    int  received_value;
    bool received_value_is_negative;
    bool received_value_first_char;

    // Pointeur vers un tableau de callbacks
    callback_t *callbacks;

} Reception_object;


void init_reception(Reception_object *values, callback_t *_callbacks);


// The main function to call at each received char
void lecture_message(char current_char, Reception_object *values);


#endif

