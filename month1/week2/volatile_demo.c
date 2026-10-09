int ready_flag = 0;
volatile int ready_flag_v = 0;
 
void wait_without_volatile(void)
{
    while (ready_flag == 0)
    {
        /* wait */
    }
}
 
void wait_with_volatile(void)
{
    while (ready_flag_v == 0)
    {
        /* wait */
    }
}
/*choose ARM GCC (a 32-bit ARM version), options -mcpu=cortex-m4 -mthumb -O2*/