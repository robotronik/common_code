#ifndef DEBUG_H
#define DEBUG_H


/**
 * Ce header contient des macro de debug.
 * On utilise un debug à plusieurs niveaux.
 *
 * On peut se fixer des normes de niveaux :
 *
 * Valeurs négatives : pour "être tranquille" pour un test
 * 0 : Désactivation totale du débug.
 * 1 : Error
 * 2 : Warn (\TODOs ?)
 * 3 : Debug
 * 4 : Verbose
 */

//////////
#if DEBUG
//////////

#include "stdio.h"

/** Affiche un message de debug
 *  Accepte n'importe quelle valeur de level
 * \note s'utilise comme printf
 */
#define debug(level, ...)       \
    if(level <= DEBUG) {        \
        printf("%d\t",level);    \
        printf(__VA_ARGS__);    \
    }


/** Affiche `byte`
 *    - sous forme d'un entier
 *    - en représentation hexa
 *    - comme un caractère
 */
#define debug_byte(level, byte)     \
    do {                            \
        unsigned char uc = byte;    \
        debug(level,                \
            "d:%d\tx:%x\tc:%c\n",   \
         uc, uc, (uc==0)? '0': uc); \
    } while(0)

//////////////
#else // DEBUG
//////////////

#define debug(level, ...)

#define debug_byte(byte)

//////////////
#endif // DEBUG
//////////////

#endif /* DEBUG_H */
