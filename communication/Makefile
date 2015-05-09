# Options:
#     ARCH: PC, PIC, STM32
#     ROBOT: GROS, PETIT
#     DEBUG: 0, 1, 2, 3, 4
#
# Cibles :
#    all: comm_asser et comm_strategie
#    comm_asser: toute ce qui est en liens à la communication de la partie
#            asservissement
#    comm_strategie: toute ce qui est en liens à la communication de la partie
#            stratégie
################################################################################

# Options
ARCH  = PC
ROBOT = gros
DEBUG = _WARNING_

# Constantes de compilation

PC_EXEC    = asser_robot

PC_CC      = gcc
PC_CFLAGS  = -DPIC_BUILD=0 -W -Wall -std=c99 -fdiagnostics-color=auto -I.
PC_LDFLAGS = -lm -lpthread

PIC_ELF    = $(PC_EXEC).elf
PIC_HEX    = $(PC_EXEC).hex
PIC_CC     = /opt/xc16-toolchain-bin/bin/xc16-gcc
PIC_ELF2HEX= /opt/xc16-toolchain-bin/bin/xc16-bin2hex

PIC_CFLAGS = -DPIC_BUILD=1 -W -Wall -std=c99 -O0 -mcpu=33FJ128MC802 -omf=elf -msmart-io=1
PIC_LDFLAGS= -Wl,--script=p33FJ128MC802.gld,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem

################################################################################

# Modules externe

COMMON_DIR = ..
COMMON_H   = $(COMMON_DIR)/debug.h

ASSER_DIR  = ../../asservissement

################################################################################

# Gestion des options

ifeq ($(ARCH), PIC)
	EXEC    = $(PIC_ELF)
	CC      = $(PIC_CC)
	CFLAGS  = $(PIC_CFLAGS)
	LDFLAGS = $(PIC_LDFLAGS)

	F_HARDWARE_C = hardware_PIC.c
	F_REGLAGES_H = reglages_PC.h

	ifeq ($(ROBOT),petit)
		CFLAGS  += -DGROS=0 -DPETIT=1
	else
		CFLAGS  += -DGROS=1 -DPETIT=0
	endif
endif

ifeq ($(ARCH), PC)
	EXEC    = $(PC_EXEC)
	CC      = $(PC_CC)
	CFLAGS  = $(PC_CFLAGS)
	LDFLAGS = $(PC_LDFLAGS)

	F_HARDWARE_C = hardware_PC.c
	F_REGLAGES_H = reglages_PC.h

	ifeq ($(SDL),yes)
		CFLAGS      += $(PC_SDL_CF)
		LDFLAGS     += $(PC_SDL_LDF)
		FICHIERS_C  += $(FICHIER_AFFICHAGE_C)
	endif
endif

CFLAGS += -DDEBUG=$(DEBUG) -g

ifeq ($(ARCH), STM32)
endif

################################################################################

# Cibles du projet
FICHIERS_H   = $(FICHIERS_C:.c=.h) $(COMMON_H)
SOURCEFILES += $(FICHIERS_C) $(FICHIERS_H)

# dossier de compilation
BUILDIR = build
OBJDIR = $(BUILDIR)/$(ARCH)/$(DEBUG)

# Liste des fichiers sans prefix
COMMON = a2s s2a text_emission text_reception uart
COMM_ASSER_FILE =  s2a_reception $(COMMON)
COMM_STRATEGIE_FILE = a2s_reception $(COMMON)

export ARCH
export ROBOT
export DEBUG

default: all

################################################################################

# Compilation

all: comm_asser comm_strategie

comm_asser: $(OBJDIR)/comm_asser.a

$(OBJDIR)/comm_asser.a: $(addprefix $(OBJDIR)/, $(addsuffix .o, $(COMM_ASSER_FILE)))
	ar -q $@ $^

comm_strategie: $(OBJDIR)/comm_strategie.a

$(OBJDIR)/comm_strategie.a: $(addprefix $(OBJDIR)/, $(addsuffix .o, $(COMM_STRATEGIE_FILE)))
	ar -q $@ $^

$(OBJDIR)/a2s_reception.o: a2s.h text_reception.h $(COMMON_DIR)/debug.h

$(OBJDIR)/a2s.o: a2s.h

$(OBJDIR)/a2s_reception.o: a2s.h a2s_reception.h text_reception.h $(COMMON_DIR)/debug.h

$(OBJDIR)/s2a.o: s2a.h

$(OBJDIR)/s2a_reception.o: s2a.h $(COMMON_DIR)/debug.h $(ASSER_DIR)/trajectoire.h

$(OBJDIR)/text_reception.o: text_reception.h $(COMMON_DIR)/debug.h

$(OBJDIR)/text_emission.o: text_emission.h $(COMMON_DIR)/debug.h $(COMMON_DIR)/time.h

$(OBJDIR)/uart.o: hardware/$(ARCH)/uart.c uart.h | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(COMMON_DIR)/.. -I.

$(OBJDIR)/%.o: %.c %.h | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(COMMON_DIR)/.. -I.

$(OBJDIR):
	mkdir $(OBJDIR) $ -p

################################################################################

# Cibles génériques
.PHONY: tarall clean mrproper

tarall: $(SOURCEFILES)
	tar -jcvf $(EXEC).tar.bz2 $^

clean:
	find $(BUILDIR) -name '*.o' -delete 2>/dev/null && find $(BUILDIR) -name '*.a' -delete 2>/dev/null && rmdir -p --ignore-fail-on-non-empty $(BUILDIR)/*/* || true

mrproper: clean
	rm -rf $(EXEC) $(PIC_ELF) $(PIC_HEX) $(EXEC).tar.bz2

