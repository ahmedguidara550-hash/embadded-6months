#include<stdio.h>
#include<stdint.h>

void print_bin8(uint8_t value){
    for (int bit=7;bit>=0;bit--){
        printf("%d",(value>>bit)&1);
    }
}
void show(char *label,uint8_t value){
    printf("%-22s = ",label);
    print_bin8(value);
    printf("decimal %3u hex 0x%02X \n",(unsigned)value,(unsigned)value);

}

int main(){
    /*1.set bit 4 of 0x00*/
    uint8_t bit = 0x00;
    bit = (uint8_t)(bit | (1U << 4));
    show("set bit 4 of 0x00 : ",bit);
    /*2.clear bit 0 of 0xFF*/
    uint8_t bit2 = 0xFF;
    bit2 = (uint8_t)(bit2 & ~(1U << 0));
    show("clear bit 0 of 0xFF : ",bit2);
    /*toggle bit 7 of 0x0F*/
    uint8_t bit3 = 0x0F;
    bit3 = (uint8_t) (bit3 ^ (1U << 7));
    show("toggle bit 7 of 0x0F : ",bit3);
    /*4.read bit 2 of 0x24*/
    uint8_t bit4 = 0x24;
    printf("bit 2 of 0x24 is : %s \n", ((bit4>>2) & 1U )? "ON" : "OFF");
    /*5.extract 7..4 of 0xA5*/
    uint8_t field = (uint8_t)((0xA5 >> 4) & 0x0FU);
    show("extract bits 7..4 of 0xA5 :",field);
    /*6.swap the two nibbles of 0xA5*/
    uint8_t v = 0xA5;
    uint8_t swap = (uint8_t)((v<<4) | (v>>4));
    show(" swap the two nibbles of 0xA5 : ",swap);
    return 0 ;
    /*9.swap the two bytes of 0xABCD*/
    

}