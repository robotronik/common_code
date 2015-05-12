################################################################################
# Makefile générique, appelé par la lib et les projets parallèles

################################################################################
#               Variables de compilation

# Options
# PC ou STM32
export ARCH  = PC
# yes ou no
export SDL   = no
# Niveaux de débug
export DEBUG = _ALWAYS_

################################################################################
#               Constantes de compilation






# Compilateur C et linker
CC      = gcc
AR      = ar
GDB     = gdb
LD      = ld
OBJ2HEX = 
LINKER  = 

# Précise la carte cible


#               Includes
# Indique au compilateur dans quels répertoires chercher les headers appelés
# avec la directive de préprocesseur "#include <header.h>"

INCLUDE = -I.







OTHER_OPTIONS =
#-mthumb-interwork


# Options de compilations
# 	-Os – optimize for size
CFLAGS  = -W -Wall -std=c99 $(TARGET) $(INCLUDE) $(OTHER_OPTIONS) -Os -g -DPIC_BUILD=0

# Options pour l'édition de liens
#	-Wl,--gc-sections – enable garbage collection of unused input sections
LDFLAGS = -W -Wall -std=c99 -Wl,--gc-sections -lm -lpthread


################################################################################
#               SDL

PC_SDL_CF = -DUSE_SDL=1
PC_SDL_LDF= -lSDL -lSDL_image -lGL -lGLU -lSOIL
