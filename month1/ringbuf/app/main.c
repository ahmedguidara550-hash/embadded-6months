#include<stdio.h>
#include "ringbuf.h"

int main(){
    uint8_t memory[4];
    ringbuf_t rb;
    if (!ringbuf_init(&rb,memory,sizeof(memory)))
    {
        printf("init failed\n");
        return 1;
    }
    /*try to push 6 bytes into a buffer that holds 4.*/
    for(uint8_t value = 10;value<16;value++){
        bool ok = ringbuf_push(&rb,value);
        printf("push %2u -> %s (count=%zu)\n",(unsigned)value,ok ? "ok" : "FULL",ringbuf_count(&rb));
    }
    /*read every thing back*/
    uint8_t out;
    while (ringbuf_pop(&rb,&out))
    {
        printf("pop -> %u\n",(unsigned)out);
    }
    printf("empty now? %s\n",ringbuf_is_empty(&rb) ? "yes" : "no");
    return 0;
    
    
}