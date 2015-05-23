################################################################################
# Makefile générique, appelé par la lib et les projets parallèles
# Default Options
export ARCH  = dsPIC
export ROBOT
export SDL
export DEBUG

################################################################################
# Compilateur C et linker
CC      = /opt/xc16-toolchain-bin/bin/xc16-gcc
AR      = /opt/xc16-toolchain-bin/bin/xc16-ar
RANLIB  = /opt/xc16-toolchain-bin/bin/xc16-ranlib
GDB     = 
LD      = /opt/xc16-toolchain-bin/bin/xc16-ld
OBJ2HEX = /opt/xc16-toolchain-bin/bin/xc16-bin2hex
LINKER  = 

# Précise la carte cible
TARGET  = -mcpu=33FJ128MC802

# Options de compilation spécifiques à la plateforme
CFLAGS += -DPIC_BUILD=1 -O0 -g -omf=elf -msmart-io=1
#-mthumb-interwork
LDFLAGS+= -Wl,--script=p33FJ128MC802.gld,--stack=16,--check-sections,--data-init,--pack-data,\
--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem

#               Includes
# Indique au compilateur dans quels répertoires chercher les headers appelés
# avec la directive de préprocesseur "#include <header.h>"



ifeq ($(ROBOT),petit)
	CFLAGS  += -DGROS=0 -DPETIT=1
else
	CFLAGS  += -DGROS=1 -DPETIT=0
endif
