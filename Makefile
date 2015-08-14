PROJECT= libCommon
default: all
# Options
export ARCH  = dsPIC33F
export ROBOT = gros
export SDL   = yes
export DEBUG = _WARNING_

export PARENT_DIR = ../
include $(PARENT_DIR)/hardware/common.mk





################################################################################
# Fichiers du projet

FICHIERS_C =
FICHIERS_H =

ifeq ($(ARCH), dsPIC)
	FICHIERS_C += hardware/$(ARCH)/time.c
	FICHIERS_H += time.h
endif
ifeq ($(ARCH), PC)
	ifeq ($(SDL), yes)
		FICHIERS_C += simulation/affichage.c
		FICHIERS_H += simulation/affichage.h
	endif
endif

FICHIERS_O = $(addprefix $(BUILD_DIR)/, $(FICHIERS_C:.c=.o) )
################################################################################

all: libCommon

libCommon: $(BUILD_DIR)/libCommon.a

$(BUILD_DIR)/libCommon.a: $(FICHIERS_O)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/simulation
	@mkdir -p $(BUILD_DIR)/hardware/$(ARCH)

################################################################################
# Cibles génériques

.PHONY: clean mrproper

mrproper: clean
	@echo "Hard-cleaning  $(PROJECT) directory…"
	@rm -rf $(EXEC) $(PIC_ELF) $(PIC_HEX) $(EXEC).tar.bz2
