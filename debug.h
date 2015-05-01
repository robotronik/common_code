#ifndef DEBUG_H
#define DEBUG_H


/**
 * Ce header contient des macro de debug.
 * On utilise un debug à plusieurs niveaux.
 *
 * On peut se fixer des normes de niveaux : (cf la liste de define au début de
 * ce fichier)
 *
 * 0 : Désactivation totale du débug.
 * 1 : Error
 * 2 : Warn (\TODOs ?)
 * 3 : Debug
 * 4 : Verbose
 *
 * De plus, la macro info() permet d'afficher des informations en sortie du
 * programme (sur stderr)
 *
 * Remarque: l'utilisation de `do ... while(0)` permet de s'assurer que
 * l'utilisateur à mis un point virgule après l'utilisation de la macro, et
 * permet d'utiliser des variables locales.
 *
 * Remarque: Le define DEBUG doit être défini dans le Makefile
 */

#include "stdio.h"

#if DEBUG < 0
#error Attention, pour desactiver le DEBUG, il faut mettre DEBUG a 0
#endif

#define _ALWAYS_  0
#define _ERROR_   1
#define _WARNING_ 2
#define _DEBUG_   3
#define _VERBOSE_ 4

#define info(...) fprintf(stderr, __VA_ARGS__)

/** Affiche un message de debug
 *  Accepte n'importe quelle valeur de level spécifié par le premier argument
 * \note s'utilise comme printf
 */
#define debug(level, ...)                   \
    do {                                    \
        if(level <= DEBUG) {                \
            fprintf(stderr, "%d\t",level);  \
            fprintf(stderr, __VA_ARGS__);   \
        }                                   \
    } while(0)

/** Affiche `byte`
 *    - sous forme d'un entier
 *    - en représentation hexa
 *    - comme un caractère
 */
#define debug_byte(level, byte)                                           \
    do {                                                                  \
        if(level <= DEBUG) {                                              \
            unsigned char uc = byte;                                      \
            debug(level, "d:%d\tx:%x\tc:%c\n", uc, uc, (uc==0)? '0': uc); \
        }                                                                 \
    } while(0)

#endif /* DEBUG_H */
