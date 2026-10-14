#======settings========
CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wconversion -Werror -O0 -g 
INCLUDES := -Iinclude
BUILD := build

LIB_SRC := src/ringbuf.c
APP_SRC := app/main.c

LIB_OBJ := $(LIB_SRC:%.c=$(BUILD)/%.o)
APP_OBJ := $(APP_SRC:%.c=$(BUILD)/%.o)
DEPS :=$(LIB_OBJ:.o=.d) $(APP_OBJ:.o=.d)

# ARM Cortex-M4 cross-compiler settings
ARM_CC := arm-none-eabi-gcc
ARM_CFLAGS :=-std=c11 -mcpu=cortex-m4 -mthumb -Os -Wall -Wextra -Wconversion -Werror

#=======targets=========
.PHONY: all size clean

all: $(BUILD)/demo

$(BUILD)/demo: $(APP_OBJ) $(LIB_OBJ)
	$(CC) $^ -o $@

size: $(BUILD)/demo
	size $(BUILD)/demo $(LIB_OBJ)

arm:
	mkdir -p $(BUILD)/arm
	$(ARM_CC) $(ARM_CFLAGS) $(INCLUDES) -c src/ringbuf.c -o $(BUILD)/arm/ringbuf.o
	arm-none-eabi-size $(BUILD)/arm/ringbuf.o

firmware:
	mkdir -p $(BUILD)/firmware
	$(ARM_CC) $(ARM_CFLAGS) -ffreestanding -nostdlib -nostartfiles \
		-ffunction-sections -fdata-sections $(INCLUDES) \
		-T baremetal/linker.ld -Wl,-Map=$(BUILD)/firmware/firmware.map -Wl,--gc-sections \
		baremetal/startup.c baremetal/main.c src/ringbuf.c -o $(BUILD)/firmware/firmware.elf
	arm-none-eabi-size $(BUILD)/firmware/firmware.elf
#one rule that builds ANY .o file from the .c file with the same name
$(BUILD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	rm -rf $(BUILD)

-include $(DEPS)