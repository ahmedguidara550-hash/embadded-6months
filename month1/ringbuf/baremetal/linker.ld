/* Minimal linker script for an STM32F407 (1MB FLASH , 128 KB RAM)*/
ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);  /*the stack starts at the end of RAM */

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))    /*the vector table must be first in Flash */
    } > FLASH

    .text :
    {
        *(.text*)    /*for my code*/
        *(.rodata*)  /*constants*/
    }>FLASH

    _sidata = LOADADDR(.data);   /*where the initial values of .data sit in Flash */

    .data :
    {
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = 0;
    }> RAM AT > FLASH

    .bss :
    {
        _sbss = .;
        *(.bss*)       /*variables without an initial value */
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > RAM
}