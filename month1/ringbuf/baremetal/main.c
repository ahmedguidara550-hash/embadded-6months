#include<stdint.h>
#include "ringbuf.h"

uint32_t value_in_data = 1234U;   /*has an initial value -> .data*/
uint32_t value_in_bss;     /*has initial value -> .bss*/

static uint8_t storage[64];
static ringbuf_t rb;

int main(void){
    (void)ringbuf_init(&rb,storage,sizeof(storage));
    for(;;){
        uint8_t tmp = 0U;
        value_in_bss++;
        (void)ringbuf_push(&rb,(uint8_t)value_in_bss);
        (void)ringbuf_pop(&rb,&tmp);
        value_in_data +=tmp;
    }
}