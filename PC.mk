################################################################################
# Makefile générique, appelé par la lib et les projets parallèles
# Default Options
export ARCH  = PC
export ROBOT
export SDL
export DEBUG

################################################################################
# Compilateur C et linker
CC      = gcc
AR      = ar
RANLIB  = ranlib
GDB     = gdb
LD      = ld
OBJ2HEX = 
LINKER  = 

# Précise la carte cible
TARGET  =

# Options de compilation spécifiques à la plateforme
CFLAGS += -DPIC_BUILD=0 -Os -g

LDFLAGS+= -Wl,--gc-sections -lm -lpthread
#	-Wl,--gc-sections – enable garbage collection of unused input sections

#               Includes
# Indique au compilateur dans quels répertoires chercher les headers appelés
# avec la directive de préprocesseur "#include <header.h>"



ifeq ($(SDL),yes)
	CFLAGS  += -DUSE_SDL=1
	LDFLAGS += -lSDL -lSDL_image -lGL -lGLU -lSOIL
endif
