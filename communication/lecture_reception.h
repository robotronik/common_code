#ifndef COMMUNICATION_LECTURE_RECEPTION
#define COMMUNICATION_LECTURE_RECEPTION

#include "keys.h"


int init_reception(callback_t *_callbacks);
int get_received_value();

void lecture_message(char current_char);


#endif
