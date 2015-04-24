
# Options prises en compte :
#    DEBUG=yes     pour activer le debug
#
# Cibles :
#    all: créer les .o

################################################################################

# Valeur par défaut

CC = gcc

CFLAGS  = -W -Wall -fdiagnostics-color=auto -std=c99
LDFLAGS = -lm

# options
DEBUG = no

################################################################################

# Modules externe

COMMON_DIR =../common_code
COMMON_H   = $(COMMON_DIR)/*.h

################################################################################

# Fichiers du projet

FICHIERS_C=\
	emission_binaire.c\
	reception_binaire.c\
	text_reception.c\
	uart_hardware.c

FICHIERS_H =

SOURCEFILES =\
	unit_test_binaire.c

EXEC = test

################################################################################

# Gestion des options

ifeq ($(DEBUG),yes)
	CFLAGS += -DDEBUG=1 -g
endif

################################################################################

# Cibles du projet

FICHIERS_H  += $(FICHIERS_C:.c=.h) $(COMMON_H)
FICHIERS_O  += $(FICHIERS_C:.c=.o)
SOURCEFILES += $(FICHIERS_C) $(FICHIERS_H)

.PHONY: test

all: $(FICHIERS_O)

test: unit_test_binaire.c $(FICHIERS_O)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./$@

%.o: %.c %.h $(COMMON_H)
	$(CC) $(CFLAGS) -o $@ -c $<

################################################################################

# Cibles génériques

tarall: $(SOURCEFILES)
	tar -jcvf $(EXEC).tar.bz2 $^

clean:
	rm -f $(FICHIERS_O)

mrproper: clean
	rm -rf $(EXEC) $(EXEC).tar.bz2

