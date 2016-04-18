PROJECT=communication_new
default: all
# Default Options
export ARCH  ?= libopencm3
export DEBUG ?= _WARNING_

PARENT_DIR = ../../




include $(PARENT_DIR)/hardware/common.rules
################################################################################
# Fichiers du projet

SRC = keys.c emission.c reception.c lecture_reception.c

OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o) )

################################################################################
# Compilation

# Règles de compilation de la "librairie communication"
all: _libComm

_libComm: $(BUILD_DIR)/libComm.a

$(BUILD_DIR)/libComm.a: $(OBJ)

#$(BUILD_DIR)/a2s.o: a2s.h


$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
