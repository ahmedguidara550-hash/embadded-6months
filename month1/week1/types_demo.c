#include<stdio.h>
#include<stdint.h>

int main(){
    /*1.How big is each type ?*/
    printf("sizeof(char) =%zu bytes\n",sizeof(char));
    printf("sizeof(short) =%zu bytes\n",sizeof(short));
    printf("sizeof(int) =%zu bytes\n",sizeof(int));
    printf("sizeof(long) =%zu bytes\n",sizeof(long));
    printf("sizeof(uint8_t) =%zu bytes\n",sizeof(uint8_t));
    printf("sizeof(uint16_t) =%zu bytes\n",sizeof(uint16_t));
    printf("sizeof(uint32_t) =%zu bytes\n",sizeof(uint32_t));
    printf("sizeof(uint64_t) =%zu bytes\n",sizeof(uint64_t));
    /*2.the odometer : wrap-around*/
    uint8_t counter = 250;
    for (int i =0;i<8;i++){
        printf("counter = %u\n",(unsigned)counter);
        counter++;
    }
    /*3.signed numbers*/
    int8_t small = 127;
    small = (int8_t)(small + 1);
    printf("int8_t 127+1 =%d",small);
    /*4. integer promotion*/
    uint8_t a= 200;
    uint8_t b= 100;
    printf("a+b = %d\n",a+b);
    uint8_t c = (uint8_t)(a+b);
    printf("stored in uint8_t = %u\n",(unsigned)c);
    /*5.integer division*/
    printf("7/2 = %d\n",7/2);
    printf("7%%2 = %d\n",7%2);
    printf("7.0/2 = %f\n",7.0/2);
    return 0;
}
