PROJECT=communication
default: all
# Default Options
export ARCH  ?= stm32f407
export ROBOT ?= gros
export SDL   ?= yes
export DEBUG ?= _WARNING_

export PARENT_DIR = ../../
include $(PARENT_DIR)/hardware/common.mk

################################################################################
# Fichiers du projet

COMMON = a2s s2a text_emission text_reception
COMM_ASSER_FILE = s2a_reception $(COMMON)
COMM_STRAT_FILE = a2s_reception $(COMMON)

################################################################################
# Compilation

all: libCommAsser libCommStrat

libCommAsser: $(BUILD_DIR)/libCommAsser.a
libCommStrat: $(BUILD_DIR)/libCommStrat.a

$(BUILD_DIR)/libCommAsser.a: $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(COMM_ASSER_FILE)))
$(BUILD_DIR)/libCommStrat.a: $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(COMM_STRAT_FILE)))

$(BUILD_DIR)/a2s.o: a2s.h
$(BUILD_DIR)/a2s_reception.o: a2s.h a2s_reception.h text_reception.h $(COMMON_DIR)/debug.h

$(BUILD_DIR)/s2a.o: s2a.h
$(BUILD_DIR)/s2a_reception.o: s2a.h s2a_reception.h text_reception.h $(COMMON_DIR)/debug.h $(ASSER_DIR)/trajectoire.h

$(BUILD_DIR)/text_reception.o: text_reception.h $(COMMON_DIR)/debug.h
$(BUILD_DIR)/text_emission.o:  text_emission.h  $(COMMON_DIR)/debug.h

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/hardware/$(ARCH)

################################################################################
# Cibles génériques

mrproper: clean
	rm -f *.a
	rm -f $(PIC_ELF) $(PIC_HEX)
