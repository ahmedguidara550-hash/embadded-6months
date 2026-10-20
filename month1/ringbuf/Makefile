#======settings========
CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wconversion -Werror -O0 -g 
INCLUDES := -Iinclude
BUILD := build

LIB_SRC := src/ringbuf.c
APP_SRC := app/main.c
TEST_SRC := test/test_ringbuf.c test/unity/unity.c

LIB_OBJ := $(LIB_SRC:%.c=$(BUILD)/%.o)
APP_OBJ := $(APP_SRC:%.c=$(BUILD)/%.o)
TEST_OBJ := $(TEST_SRC:%.c=$(BUILD)/%.o)
DEPS     := $(LIB_OBJ:.o=.d) $(APP_OBJ:.o=.d) $(TEST_OBJ:.o=.d)

# ARM Cortex-M4 cross-compiler settings
ARM_CC := arm-none-eabi-gcc
ARM_CFLAGS :=-std=c11 -mcpu=cortex-m4 -mthumb -Os -Wall -Wextra -Wconversion -Werror

#=======targets=========
.PHONY: all test size arm firmware coverage analyze clean

all: $(BUILD)/demo

$(BUILD)/demo: $(APP_OBJ) $(LIB_OBJ)
	$(CC) $^ -o $@

$(BUILD)/test_ringbuf: $(TEST_OBJ) $(LIB_OBJ)
	$(CC) $^ -o $@

test : $(BUILD)/test_ringbuf
	./$(BUILD)/test_ringbuf

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

analyze:
	cppcheck --enable=all --inconclusive --std=c11 --suppress=missingIncludeSystem -Iinclude src/ app/
	clang-tidy src/ringbuf.c -- -std=c11 -Iinclude
	$(CC) -std=c11 -fanalyzer -Wall -Wextra $(INCLUDES) -c src/ringbuf.c -o /dev/null

coverage:
	rm -rf $(BUILD)/cov && mkdir -p $(BUILD)/cov
	$(CC) -std=c11 -O0 -g --coverage $(INCLUDES) -Itest/unity \
		test/test_ringbuf.c test/unity/unity.c src/ringbuf.c -o $(BUILD)/cov/test_cov
	cd $(BUILD)/cov && ./test_cov
	cd $(BUILD)/cov && lcov --capture --directory . --output-file all.info --rc branch_coverage=1 --ignore-errors mismatch,inconsistent
	cd $(BUILD)/cov && lcov --extract all.info '*/src/ringbuf.c' --output-file ringbuf.info --rc branch_coverage=1
	cd $(BUILD)/cov && genhtml ringbuf.info --output-directory html --rc branch_coverage=1
	@echo "Open $(BUILD)/cov/html/index.html in your browser"

#one rule that builds ANY .o file from the .c file with the same name
$(BUILD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -Itest/unity -MMD -MP -c $< -o $@
clean:
	rm -rf $(BUILD)

-include $(DEPS)