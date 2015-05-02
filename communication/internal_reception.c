#include <ctype.h>

#include "internal_reception.h"

void prepare_current_char(char *current_char)
{
    // on ne tient pas compte de la casse
    *current_char = tolower(*current_char);
}

bool is_whitespace(char c)
{
    return (c == ' ') || (c == '\t');
}

