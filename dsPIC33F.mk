################################################################################
# Makefile générique, appelé par la lib et les projets parallèles

################################################################################
#               Variables de compilation

# Options
# PC ou STM32
export ARCH  = PIC
# yes ou no
export SDL   = no
# Niveaux de débug
export DEBUG = _ALWAYS_

################################################################################
#               Constantes de compilation






# Compilateur C et linker
CC      = /opt/xc16-toolchain-bin/bin/xc16-gcc
AR      = /opt/xc16-toolchain-bin/bin/xc16-ar
GDB     = 
LD      = /opt/xc16-toolchain-bin/bin/xc16-ld
OBJ2HEX = /opt/xc16-toolchain-bin/bin/xc16-bin2hex
LINKER  = 

# Précise la carte cible
TARGET  = -mcpu=33FJ128MC802

#               Includes
# Indique au compilateur dans quels répertoires chercher les headers appelés
# avec la directive de préprocesseur "#include <header.h>"

INCLUDE =







OTHER_OPTIONS = -omf=elf -msmart-io=1
#-mthumb-interwork


# Options de compilations
# 	-Os – optimize for size
CFLAGS  = -W -Wall -std=c99 $(TARGET) $(INCLUDE) $(OTHER_OPTIONS) -O0 -DPIC_BUILD=1

# Options pour l'édition de liens
#	-Wl,--gc-sections – enable garbage collection of unused input sections
LDFLAGS = -W -Wall -std=c99 -Wl,--script=p33FJ128MC802.gld,--stack=16,\
--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,\
--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem


################################################################################
#               Règles génériques
