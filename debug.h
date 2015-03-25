#ifndef DEBUG_H
#define DEBUG_H


/**
 * Ce header contient des macro de debug.
 * Pour les activer, il faut definir 'DEBUG' à une valeur non nulle
 * Si 'DEBUG' est non défini ou nul, alors les macros suivantes sont sans effet
 */

//////////
#if !DEBUG
//////////

/** Affiche un message de debug
 * \note s'utilise comme printf
 */
#define debug(...)

/** Affiche `byte`
 *    - sous forme d'un entier
 *    - en représentation hexa
 *    - comme un caractère
 */
#define debug_byte(byte)

//////////////
#else // DEBUG
//////////////

#include "stdio.h"

#define debug(...) printf(__VA_ARGS__)

#define debug_byte(byte)                  \
    do {                                  \
        char c = byte;                    \
        debug("\t");                      \
        debug("d:%d",c);                  \
        debug("\t");                      \
        debug("x:%x",c);                  \
        debug("\t");                      \
        debug("c:%c", (c==0)? '0': c);    \
        debug("\n", c);                   \
    } while(0)

//////////////
#endif // DEBUG
//////////////

#endif /* DEBUG_H */
