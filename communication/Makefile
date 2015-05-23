PROJECT=communication

# Default Options
export ARCH  = STM32F407
export ROBOT = gros
export SDL   = yes
export DEBUG = _WARNING_

export PARENT_DIR = ../../
include $(PARENT_DIR)/common_code/common.mk

# Constantes de compilation
EXEC    = libCommunication



################################################################################
# Fichiers du projet

COMMON = a2s s2a text_emission text_reception uart
COMM_ASSER_FILE = s2a_reception $(COMMON)
COMM_STRAT_FILE = a2s_reception $(COMMON)

################################################################################
# Compilation

all: libCommAsser libCommStrat

libCommAsser: $(BUILD_DIR)/libCommAsser.a
libCommStrat: $(BUILD_DIR)/libCommStrat.a

$(BUILD_DIR)/libCommAsser.a: $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(COMM_ASSER_FILE)))
$(BUILD_DIR)/libCommStrat.a: $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(COMM_STRAT_FILE)))

$(BUILD_DIR)/%.a:
	@echo "	AR	$(PROJECT)|$(notdir $@)"
	@$(AR) -q $@ $^
	@echo "	RANLIB	$(PROJECT)|$(notdir $@)"
	@$(RANLIB) $@


$(BUILD_DIR)/a2s.o: a2s.h
$(BUILD_DIR)/a2s_reception.o: a2s.h a2s_reception.h text_reception.h $(COMMON_DIR)/debug.h

$(BUILD_DIR)/s2a.o: s2a.h
$(BUILD_DIR)/s2a_reception.o: s2a.h s2a_reception.h text_reception.h $(COMMON_DIR)/debug.h $(ASSER_DIR)/trajectoire.h

$(BUILD_DIR)/text_reception.o: text_reception.h $(COMMON_DIR)/debug.h
$(BUILD_DIR)/text_emission.o:  text_emission.h  $(COMMON_DIR)/debug.h $(COMMON_DIR)/time.h

$(BUILD_DIR)/%.o: %.c %.h | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/uart.o: hardware/$(ARCH)/uart.c uart.h | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p

################################################################################

# Cibles génériques
.PHONY: tarall clean mrproper

clean:
	@echo "Cleaning build directory…"
	@find $(BUILDIR) -name '*.o' -delete
	@find $(BUILDIR) -name '*.a' -delete	
	@rm -f *.a

mrproper: clean
	rm -f *.a
	rm -f $(EXEC) $(PIC_ELF) $(PIC_HEX)
