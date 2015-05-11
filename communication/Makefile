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
export ARCH  = STM32
export ROBOT = gros
export DEBUG = _WARNING_

# Constantes de compilation

ifeq ($(ARCH), STM32)
	PathSTM32 = ../../stm32f407/
	include ../../stm32f407/stm32f407.mk
	CFLAGS += -I./
else
ifeq ($(ARCH), PIC)
	EXEC    = $(PC_EXEC).elf
	PIC_HEX = $(PC_EXEC).hex
	include ../dsPIC33F.mk
else
ifeq ($(ARCH), PC)
	EXEC    = asser_robot
	include ../PC.mk

	ifeq ($(SDL),yes)
		CFLAGS      += $(PC_SDL_CF)
		LDFLAGS     += $(PC_SDL_LDF)
		FICHIERS_C  += $(FICHIER_AFFICHAGE_C)
	endif
else
#Erreur !
error:
	@echo "Mauvaise ARCH !"
	exit 1
endif
endif
endif

ifeq ($(ROBOT),petit)
	CFLAGS  += -DGROS=0 -DPETIT=1
else
	CFLAGS  += -DGROS=1 -DPETIT=0
endif
CFLAGS += -DDEBUG=$(DEBUG)


################################################################################

# Modules externe

COMMON_DIR = ../
COMMON_H   = $(COMMON_DIR)/debug.h

ASSER_DIR  = ../../asservissement

################################################################################

# Gestion des options


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
	@echo "	AR	$@"
	@ar -q $@ $^

comm_strategie: comm_strategie.a

comm_strategie.a: $(OBJDIR)/comm_strategie.a
	cp $^ $@

$(OBJDIR)/comm_strategie.a: $(addprefix $(OBJDIR)/, $(addsuffix .o, $(COMM_STRATEGIE_FILE)))
	@echo "	AR	$@"
	@ar -q $@ $^

$(OBJDIR)/a2s_reception.o: a2s.h text_reception.h $(COMMON_DIR)/debug.h

$(OBJDIR)/a2s.o: a2s.h

$(OBJDIR)/a2s_reception.o: a2s.h a2s_reception.h text_reception.h $(COMMON_DIR)/debug.h

$(OBJDIR)/s2a.o: s2a.h

$(OBJDIR)/s2a_reception.o: s2a.h $(COMMON_DIR)/debug.h $(ASSER_DIR)/trajectoire.h

$(OBJDIR)/text_reception.o: text_reception.h $(COMMON_DIR)/debug.h

$(OBJDIR)/text_emission.o: text_emission.h $(COMMON_DIR)/debug.h $(COMMON_DIR)/time.h

$(OBJDIR)/uart.o: hardware/$(ARCH)/uart.c uart.h | $(OBJDIR)
	@echo "	CC	$@"
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(COMMON_DIR)/.. -I.

$(OBJDIR)/%.o: %.c %.h | $(OBJDIR)
	@echo "	CC	$@"
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(COMMON_DIR)/.. -I.

$(OBJDIR):
	mkdir $(OBJDIR) $ -p

################################################################################

# Cibles génériques
.PHONY: tarall clean mrproper

tarall: $(SOURCEFILES)
	tar -jcvf $(EXEC).tar.bz2 $^

clean:
	@echo "Cleaning build directory…"
	@find $(BUILDIR) -name '*.o' -delete -o -name '*.a'
	@rmdir -p --ignore-fail-on-non-empty $(BUILDIR)/*/* || true

mrproper: clean
	rm -f *.a
	rm -f $(EXEC) $(PIC_ELF) $(PIC_HEX) $(EXEC).tar.bz2

