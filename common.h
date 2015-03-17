#ifndef COMMON_H
#define COMMON_H

#include "stdio.h"
//#define debug(...) printf(__VA_ARGS__)
#define debug(...)

#define debug_byte(byte)                            \
    do {                                            \
        char c = byte;                              \
        debug("\t");                                \
        debug("d:%d",c);                         \
        debug("\t");                                \
        debug("x:%x",c);                         \
        debug("\t");                                \
        debug("c:%c", (c==0)? '0': c);        \
        debug("\n", c);                          \
    } while(0)

#endif // COMMON_H
