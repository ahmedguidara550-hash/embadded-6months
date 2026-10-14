#include<stdint.h>

/*these symbols are created by the linker script */
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void Reset_Handler(void){
    /*step1: copy the initial values of .data from Flash to RAM*/
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata){
        *dst = *src;
        dst++;
        src++;
    }
    /*step2 : fill .bss with zeros */
    for (dst = &_sbss; dst < &_ebss;dst++){
        *dst = 0U;
    }
    /*step3 : run the real program*/
    (void)main();

    /*main() should never return but if it does stay here*/
    for (;;)
    {
    }
}

void Default_Handler(void){
    for (;;)
    {
    }
}

/*the vector table : the CPU reads the first two entries at power-up. */
__attribute__((section(".isr_vector"),used))
const uint32_t vector_table[] =
{
    (uint32_t)&_estack, /*entry 0 : initial stack pointer*/
    (uint32_t)Reset_Handler, /*entry 1 : where to start running*/
    (uint32_t)Default_Handler, /*entry 2 :NMI*/
    (uint32_t)Default_Handler, /*entry 3 : HardFault*/
};