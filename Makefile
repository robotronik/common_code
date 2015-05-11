# Options
export ARCH  = PIC
export ROBOT = gros
export SDL   = yes
export DEBUG = _WARNING_

################################################################################

# dossier de compilation
BUILDIR = build
OBJDIR = $(BUILDIR)/$(ARCH)/$(DEBUG)

################################################################################
# Flags dépendant des architectures

ifeq ($(ARCH), PIC)
	CFLAGS += -DPIC_BUILD=1 -W -Wall -std=c99 -O0 -mcpu=33FJ128MC802 -omf=elf -msmart-io=1
	LDFLAGS = -Wl,--script=p33FJ128MC802.gld,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem
	CC      = /opt/xc16-toolchain-bin/bin/xc16-gcc
	ELF2HEX = /opt/xc16-toolchain-bin/bin/xc16-bin2hex
endif

################################################################################

LIB_FILE = 

ifeq ($(ARCH), PIC)
	LIB_FILE += time
endif

################################################################################

all: libCommon
	@echo fin du build pour $(ARCH)

libCommon: $(OBJDIR)/libCommon.a | $(OBJDIR)

ifeq ($(ARCH), $(filter $(ARCH), PC STM32))
libCommon:
	touch $(OBJDIR)/libCommon.a # pour les archi qui ne fabriquent pas encore le .a (rien a mettre dedans)
endif

$(OBJDIR)/libCommon.a: $(addprefix $(OBJDIR)/, $(addsuffix .o, $(LIB_FILE))) | $(OBJDIR)
	ar -q $@ $^

$(OBJDIR)/time.o: hardware/$(ARCH)/time.c | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o: %.c %.h | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR):
	mkdir $(OBJDIR) $ -p

################################################################################

# Cibles génériques
.PHONY: tarall clean mrproper

clean:
	find $(BUILDIR) -name '*.o' -delete 2>/dev/null && find $(BUILDIR) -name '*.a' -delete 2>/dev/null && rmdir -p --ignore-fail-on-non-empty $(BUILDIR)/*/* || true

mrproper: clean
	rm -rf $(EXEC) $(PIC_ELF) $(PIC_HEX) $(EXEC).tar.bz2

