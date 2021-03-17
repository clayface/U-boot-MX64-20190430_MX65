ifndef CONFIG_SYS_TEXT_BASE
ifdef CONFIG_NAND_IPROC_BOOT
CONFIG_SYS_TEXT_BASE = 0x1C000000
else
CONFIG_SYS_TEXT_BASE = 0x1E000000
endif
endif

ifdef CONFIG_NO_CODE_RELOC
LDSCRIPT := $(SRCTREE)/board/$(BOARDDIR)/u-boot-nr.lds
endif

ifdef CONFIG_CUSTOM_LINKER_SCRIPT
LDSCRIPT := $(SRCTREE)/board/$(BOARDDIR)/u-boot-custom.lds
endif
#PLATFORM_RELFLAGS += -DSVN_REVISION=' " $(SVN_REV)"'
