PROJECT=     libCommon

# Options
export ARCH  = dsPIC
export ROBOT = gros
export SDL   = yes
export DEBUG = _WARNING_

export PARENT_DIR = ../
include $(PARENT_DIR)/common_code/common.mk






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
.PHONY: $(BUILD_DIR)

all: libCommon

libCommon: $(BUILD_DIR)/libCommon.a

$(BUILD_DIR)/libCommon.a: $(FICHIERS_O)
	@echo "	AR	$(PROJECT)|$(notdir $@)"
	@$(AR) -q $@ $^
	@echo "	RANLIB	$(PROJECT)|$(notdir $@)"
	@$(RANLIB) $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/simulation
	@mkdir -p $(BUILD_DIR)/hardware/$(ARCH)

################################################################################
# Cibles génériques

.PHONY: clean mrproper

clean:
	@echo "Cleaning $(PROJECT) directory…"
	@find $(BUILD_DIR) -name '*.o' -delete
	@find $(BUILD_DIR) -name '*.a' -delete
	@rmdir -p --ignore-fail-on-non-empty $(BUILD_DIR)/*/* 2>/dev/null || true

mrproper: clean
	@echo "Hard-cleaning  $(PROJECT) directory…"
	@rm -rf $(EXEC) $(PIC_ELF) $(PIC_HEX) $(EXEC).tar.bz2
