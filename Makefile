# STM32F030F4P6  (4KB SRAM, 16KB FLASH, F=20pin, 4=16KB flash, P=TSSOP, 6=-40to85 degC)
# Use STM32F030x6 in STM32 Cube

ifndef STLINK
$(error STLINK is not set)
endif

ifndef TOOL_BASE_GENERIC
$(error TOOL_BASE_GENERIC not set)
endif


TOOL_PATH=$(TOOL_BASE_GENERIC)/bin
CC      =$(TOOL_PATH)/arm-none-eabi-gcc
LD      =$(TOOL_PATH)/arm-none-eabi-ld
OBJCOPY =$(TOOL_PATH)/arm-none-eabi-objcopy
SIZE    =$(TOOL_PATH)/arm-none-eabi-size
GDB     =$(TOOL_PATH)/arm-none-eabi-gdb
OBJDUMP =$(TOOL_PATH)/arm-none-eabi-objdump
READELF =$(TOOL_PATH)/arm-none-eabi-readelf

FLASH_START=0x8000000
PROJ_NAME=first

OBJ_DIR = build

C_FLAGS  = -g -O2 -Wall
C_FLAGS += -mlittle-endian -mthumb -mthumb-interwork
C_FLAGS += -mcpu=cortex-m0
C_FLAGS += -fno-stack-protector
C_FLAGS += -msoft-float
C_FLAGS += -I CMSIS

LD_FLAGS = -Tlink.ld
LD_FLAGS += -Wl,-Map=$(OBJ_DIR)/$(PROJ_NAME).map
LD_FLAGS += -lc -lg -lgcc
LD_FLAGS += -nostartfiles
LD_FLAGS += -mcpu=cortex-m0
LD_FLAGS += -mlittle-endian -mthumb -mthumb-interwork
LD_FLAGS += -Wl,--build-id=none

# Find all top level c files.
SRCS=$(wildcard *.c)
# Build up the required top level objects
OBJS_TOP=$(SRCS:%.c=$(OBJ_DIR)/%.o)


OBJS_ALL = $(OBJS_TOP)
OBJS_ALL += $(OBJ_DIR)/startup.o

all: $(OBJ_DIR)/$(PROJ_NAME).bin

$(OBJ_DIR)/startup.o: startup.s
	@ echo $@
	@ $(CC) -c -o $@ $(C_FLAGS) $<

# Pattern rule for all .o files, but only the ones in OBJS_TOP. Output in build directory
$(filter %.o,$(OBJS_TOP)): $(OBJ_DIR)/%.o: %.c
	@ echo $@
	@ $(CC) -c -o $@ $(C_FLAGS) -Wa,-ahlms=$@.lst  $<

$(OBJ_DIR)/$(PROJ_NAME).elf: $(OBJS_ALL)
	@ echo $@
	$(CC) $^ $(LD_FLAGS) -o $@

$(OBJ_DIR)/$(PROJ_NAME).bin: $(OBJ_DIR)/$(PROJ_NAME).elf
	@ echo $@
	@ $(OBJCOPY) -O binary $< $@

dis_bin: $(OBJ_DIR)/$(PROJ_NAME).bin
	$(OBJDUMP) -D -b binary -m arm $<

dis: $(OBJ_DIR)/$(PROJ_NAME).elf
	$(OBJDUMP) -d $<

flash: $(OBJ_DIR)/$(PROJ_NAME).bin
	$(STLINK)/st-flash write $<  $(FLASH_START)

clean:
	rm -f build/*

