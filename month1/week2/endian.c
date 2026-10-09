#include<stdio.h>
#include<stdint.h>

int main(){
    uint32_t number = 0x12345678U ;
    uint8_t *bytes = (uint8_t *)&number;
    for (int i = 0; i < 4; i++)
    {
        printf("byte %d (address +%d) = 0x%02X\n",i,i,(unsigned)bytes[i]);
    }
    return 0;
    
}