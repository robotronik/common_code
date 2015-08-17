PROJECT= libCommon
default: libCommon
# Options
export ARCH  ?= dsPIC33F
export ROBOT ?= gros
export SDL   ?= yes
export DEBUG ?= _WARNING_

PARENT_DIR = ../

# Constantes de compilation
LIBCOMMON=libCommon.a


include $(PARENT_DIR)/hardware/common.mk
################################################################################
# Fichiers du projet

FICHIERS_C =
FICHIERS_H =

ifeq ($(ARCH), PC)
	ifeq ($(SDL), yes)
		FICHIERS_C += simulation/affichage.c
		FICHIERS_H += simulation/affichage.h
	endif
endif

FICHIERS_O = $(addprefix $(BUILD_DIR)/, $(FICHIERS_C:.c=.o) )

################################################################################


libCommon: $(BUILD_DIR)/libCommon.a

$(BUILD_DIR)/libCommon.a: $(FICHIERS_O)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/simulation

################################################################################
# Cibles génériques

mrproper: clean
	@echo "Hard-cleaning  $(PROJECT) directory…"
	@rm -rf $(EXEC)
