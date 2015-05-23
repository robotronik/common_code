PROJECT=     libCommon

# Options
export ARCH  = dsPIC
export ROBOT = gros
export SDL   = yes
export DEBUG = _WARNING_

export PARENT_DIR = ../
include $(PARENT_DIR)/common_code/common.mk


# dossier de compilation
BUILD_DIR = build/$(ARCH)/$(DEBUG)

################################################################################

ifeq ($(ARCH), dsPIC)
	LIB_FILE += time
endif
ifeq ($(ARCH), PC)
	ifeq ($(SDL), yes)
		LIB_FILE += simulation/affichage
	endif
endif

################################################################################

all: libCommon
	@echo fin du build pour $(ARCH)

libCommon: $(BUILD_DIR)/libCommon.a | $(BUILD_DIR)

$(BUILD_DIR)/libCommon.a: $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(notdir $(LIB_FILE)))) | $(BUILD_DIR)
	@echo "	AR	$(PROJECT)|$(notdir $@)"
	$(AR) -q $@ $^
	@echo "	RANLIB	$(PROJECT)|$(notdir $@)"
	@$(RANLIB) $@

$(BUILD_DIR)/affichage.o: simulation/affichage.c
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/time.o: hardware/$(ARCH)/time.c | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/%.o: %.c %.h | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p

################################################################################
# Cibles génériques

.PHONY: clean mrproper

clean:
	@echo "Cleaning $(PROJECT) directory…"
	@find $(BUILDIR) -name '*.o' -delete
	@find $(BUILDIR) -name '*.a' -delete
	@rmdir -p --ignore-fail-on-non-empty $(BUILD_DIR)/*/* 2>/dev/null || true

mrproper: clean
	@echo "Hard-cleaning  $(PROJECT) directory…"
	@rm -rf $(EXEC) $(PIC_ELF) $(PIC_HEX) $(EXEC).tar.bz2
