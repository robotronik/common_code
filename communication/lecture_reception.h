#ifndef COMMUNICATION_LECTURE_RECEPTION
#define COMMUNICATION_LECTURE_RECEPTION

#include "keys.h"

// Needs to be called to init the callbacks and the reception structure
int init_reception(callback_t *_callbacks);

// Can be called by the callbacks to get the received value
int get_received_value();

// The main function to call at each received char
void lecture_message(char current_char);


#endif
