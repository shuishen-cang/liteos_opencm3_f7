OUTDIR 			= 	build/
BINARY 			= 	Demo

ALL_INC 		+= 	
ALL_SRC    		= 	main.c 					

include app/app.mk
include hal/hal.mk
include LiteOS/liteos.mk


ASRCS  			= $(wildcard $(ALL_SRCA))
CSRCS  			= $(wildcard $(ALL_SRC))
COBJS 			:= $(CSRCS:.c=.o)
AOBJS 			:= $(ASRCS:.s=.o)


LIBNAME			= opencm3_stm32f7
DEFS			+= -DSTM32F7

FP_FLAGS		?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS		= -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

OOCD			?= openocd
OOCD_INTERFACE	?= stlink-v2-1
OOCD_TARGET		?= stm32f7x

PREFIX	?= arm-none-eabi
CC		:= $(PREFIX)-gcc
CXX		:= $(PREFIX)-g++
LD		:= $(PREFIX)-gcc
AR		:= $(PREFIX)-ar
AS		:= $(PREFIX)-as
OBJCOPY	:= $(PREFIX)-objcopy
OBJDUMP	:= $(PREFIX)-objdump
GDB		:= $(PREFIX)-gdb
STFLASH		= $(shell which st-flash)
STYLECHECK	:= /checkpatch.pl
STYLECHECKFLAGS	:= --no-tree -f --terse --mailback
STYLECHECKFILES	:= $(shell find . -name '*.[ch]')
OPT			:= -Os
DEBUG		:= -ggdb3
CSTD		?= -std=c99

OPENCM3_DIR	:= /home/luocang/workspace/02STM32/01opencm3/libopencm3/

OPENCM3_SCRIPT_DIR = $(OPENCM3_DIR)/scripts
EXAMPLES_SCRIPT_DIR	= $(OPENCM3_DIR)/../scripts

###############################################################################
# C flags

TGT_CFLAGS	+= $(OPT) $(CSTD) $(DEBUG)
TGT_CFLAGS	+= $(ARCH_FLAGS)
TGT_CFLAGS	+= -Wshadow -Wimplicit-function-declaration
TGT_CFLAGS	+= -Wstrict-prototypes
TGT_CFLAGS	+= -fno-common -ffunction-sections -fdata-sections
TGT_CFLAGS	+= -fno-common -Wall -fdata-sections -ffunction-sections
###############################################################################
# C++ flags

TGT_CXXFLAGS	+= $(OPT) $(CXXSTD) $(DEBUG)
TGT_CXXFLAGS	+= $(ARCH_FLAGS)
TGT_CXXFLAGS	+= -Wshadow -Wredundant-decls  -Weffc++
TGT_CXXFLAGS	+= -fno-common -Wall -fdata-sections -ffunction-sections
###############################################################################
# C & C++ preprocessor common flags

TGT_CPPFLAGS	+= -MD
TGT_CPPFLAGS	+= -Wall -Wundef
TGT_CPPFLAGS	+= $(DEFS)

###############################################################################
# Linker flags

TGT_LDFLAGS		+= --static -nostartfiles --specs=nano.specs
TGT_LDFLAGS		+= -T$(LDSCRIPT)
TGT_LDFLAGS		+= $(ARCH_FLAGS) $(DEBUG)
TGT_LDFLAGS		+= -Wl,-Map=$(OUTDIR)$(*).map -Wl,--cref
TGT_LDFLAGS		+= -Wl,--gc-sections
ifeq ($(V),99)
TGT_LDFLAGS		+= -Wl,--print-gc-sections
endif

###############################################################################
# Used libraries

LDLIBS		+= -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

###############################################################################
###############################################################################
###############################################################################
DEFS        += $(addprefix -I,$(ALL_INC))
DEFS		+= -I$(OPENCM3_DIR)/include
LDFLAGS		+= -L$(OPENCM3_DIR)/lib
LDLIBS		+= -l$(LIBNAME)
LDSCRIPT	?= $(BINARY).ld

# DEFS		+= -IuCos-II/inc

all: elf
elf: $(BINARY).elf
flash: $(BINARY).flash

# test:
# 	@echo 

%.elf %.map: chkbindir $(AOBJS) $(COBJS) $(LDSCRIPT) $(OPENCM3_DIR)/lib/lib$(LIBNAME).a
	@$(Q)$(LD) $(TGT_LDFLAGS) $(LDFLAGS)  \
	$(addprefix $(OUTDIR),$(notdir $(AOBJS))) \
	$(addprefix $(OUTDIR),$(notdir $(COBJS))) \
	$(LDLIBS) -o $(OUTDIR)$(*).elf 

$(COBJS): %.o: %.c 
	@$(Q)$(CC) $(TGT_CFLAGS) $(CFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $(OUTDIR)$(notdir $@) -c $^

$(AOBJS): %.o: %.s 
	@$(Q)$(CC) $(TGT_CFLAGS) $(CFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $(OUTDIR)$(notdir $@) -c $^

%.flash: %.elf
	@printf "  FLASH   $<\n"
	(echo "halt; program $(realpath $(*).elf) verify reset" | nc -4 localhost 4444 2>/dev/null) || \
		$(OOCD) -f interface/$(OOCD_INTERFACE).cfg \
		-f target/$(OOCD_TARGET).cfg \
		-c "program $(OUTDIR)$(*).elf verify reset exit" \
		$(NULL)

clean:
	@#printf "  CLEAN\n"
	@$(Q)$(RM) -rf $(GENERATED_BINARIES) generated.* $(OBJS) $(OBJS:%.o=%.d) $(OUTDIR) *.map

chkbindir:
	@if test ! -d $(OUTDIR) ; \
	then \
	mkdir $(OUTDIR) ; \
	fi
