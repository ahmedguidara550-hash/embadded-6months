# ringbuf
 
A small, allocation-free ring buffer (circular FIFO) of bytes for embedded C.
Designed for UART/CAN receive queues on microcontrollers.
 
## Features
- No dynamic memory: the caller provides the storage.
- Fixed capacity chosen at initialisation.
- Defensive: every function checks for NULL pointers.
- Builds with `-Wall -Wextra -Wconversion -Werror`.
- Cross-compiles for ARM Cortex-M4 (182 bytes of code with -Os).
 
## Folder layout
| Folder     | Content                                   |
|------------|-------------------------------------------|
| include/   | public header (ringbuf.h)                 |
| src/       | implementation (ringbuf.c)                |
| app/       | demo program for the PC                   |
| baremetal/ | start-up code, linker script, firmware    |
 
## Build
    make all        # PC demo  -> build/demo
    make arm        # ringbuf.o for Cortex-M4 and its size
    make firmware   # bare-metal firmware.elf for an STM32F407-class chip
    make clean
 
Or with CMake:
    cmake -S . -B build-cmake && cmake --build build-cmake
 
## Usage
    uint8_t memory[16];
    ringbuf_t rb;
    ringbuf_init(&rb, memory, sizeof(memory));
    ringbuf_push(&rb, 42);
    uint8_t value;
    if (ringbuf_pop(&rb, &value)) { /* value == 42 */ }
 
## Design decisions
- head/tail/count are kept separately, so the buffer can hold `capacity` bytes
  (no wasted slot) and full/empty are trivial to detect.
- Not interrupt-safe or thread-safe yet. Protect it or use a single
  producer and single consumer scheme (to be studied later)
 
## Status
Unit tests and coverage: coming later
