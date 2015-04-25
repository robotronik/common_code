#ifndef DEBUG_H
#define DEBUG_H


/**
 * Ce header contient des macro de debug.
 * Pour les activer, il faut definir 'DEBUG' à une valeur non nulle
 * Si 'DEBUG' est non défini ou nul, alors les macros suivantes sont sans effet
 * Mettre une valeur élevé augmente le niveau de débug
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
        debug("\n");                   \
    } while(0)

//////////////
#endif // DEBUG
//////////////

#if DEBUG >= 1
#define debug_lvl1(...) debug(__VA_ARGS__)
#else
#define debug_lvl1(...)
#endif

#if DEBUG >= 2
#define debug_lvl2(...) debug(__VA_ARGS__)
#else
#define debug_lvl2(...)
#endif

#if DEBUG >= 3
#define debug_lvl3(...) debug(__VA_ARGS__)
#else
#define debug_lvl3(...)
#endif

#endif /* DEBUG_H */
