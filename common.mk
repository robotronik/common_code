

# Permet d'inclure les headers "d'interface" des différents projets

# Le dossier parent des différents dépôts est PARENT_DIR et doit être fourni par les
# différents Makefile.

# Les différents projets
export ASSER_DIR = $(PARENT_DIR)/asservissement/
export STRAT_DIR = $(PARENT_DIR)/strategie/
export CARTO_DIR = $(PARENT_DIR)/cartographie/

export COMMON_DIR= $(PARENT_DIR)/common_code/
export COMMUNICATION_DIR= $(COMMON_DIR)/communication/
export STM32_DIR = $(PARENT_DIR)/stm32f407/

# Le dossier de build, dans chaque dépôt
export BUILD_DIR = build/$(ARCH)/$(DEBUG)


# Options de compilations
CFLAGS += -W -Wall -std=c99 $(TARGET) $(INCLUDE) -DDEBUG=$(DEBUG)

# Options pour l'édition de liens
LDFLAGS+= -W -Wall -std=c99

# Let's include the right generic makefile
ifeq ($(ARCH), PC)
	include $(COMMON_DIR)/PC.mk
endif
ifeq ($(ARCH), dsPIC)
	include $(COMMON_DIR)/dsPIC33F.mk
endif
ifeq ($(ARCH), STM32F407)
	include $(STM32_DIR)/stm32f407.mk
endif



#ifeq ($(ARCH), STM32F429)
#	include $(STM32_DIR)/stm32f429.mk
#endif

# export COMMON_INCLUDE=	\
# -I$(CARTO_DIR) 	\
# -I$(COMMON_DIR)	\
# -I$(COMMON_DIR)/communication/	\
# -I$(STM32_DIR)/headers/	\


################################################################################
# Common Rules


# Compile an object file
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

# Compile a static library
$(BUILD_DIR)/%.a:
	@echo "	AR	$(PROJECT)|$(notdir $@)"
	@rm -f $@
	@$(AR) -r $@ $^
	@echo "	RANLIB	$(PROJECT)|$(notdir $@)"
	@$(RANLIB) $@

################################################################################
# Clean the current working directory
.PHONY: clean mrproper

clean:
	@echo "Cleaning $(PROJECT) directory…"
	@rm -rf build/
# clean:
# 	@echo "Cleaning $(PROJECT) directory…"
# 	@find $(BUILD_DIR) -name '*.o' -delete
# 	@find $(BUILD_DIR) -name '*.a' -delete
# 	@rmdir -p --ignore-fail-on-non-empty $(BUILD_DIR)/*/* 2>/dev/null || true
