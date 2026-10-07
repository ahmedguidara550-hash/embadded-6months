#include <stdio.h>
#include <stdint.h>

/*print an 8-bit value as 8 binary digits*/
void print_bin8(uint8_t value){
    for(int bit=7;bit>=0;bit--){
        printf("%d",(value >> bit)& 1);
    }
}
void show(const char *label,uint8_t value){
    printf("%-22s = ",label);
    print_bin8(value);
    printf("  (decimal %3u ,hex 0x%02X)\n",(unsigned)value,(unsigned)value);
}

int main(){
    uint8_t a= 0xCA;
    uint8_t b= 0x0F;

    show("a",a);
    show("b",b);
    show("a & b ",(uint8_t)(a & b));
    show("a | b",(uint8_t)(a | b));
    show("a ^ b",(uint8_t)(a ^ b));
    show("~a ",(uint8_t)~a);
    show("a << 1 ",(uint8_t)(a << 1));
    show("a >> 2 ",(uint8_t)(a >> 2));
    
    printf("\n--- the four classic tricks on register ---\n");
    uint8_t reg = 0x00;

    reg = (uint8_t)(reg | (1U << 3));
    show("set bit 3",reg);

    reg = (uint8_t)(reg | (1U << 0));
    show("set bit 0",reg);

    reg = (uint8_t)(reg ^ (1U << 5));
    show("toggle bit 5",reg);

    reg = (uint8_t)(reg & ~(1U << 3 ));
    show("clear bit 3",reg);

    printf("bit 5 is %s\n",((reg>>5) & 1U) ? "ON" : "OFF");
    printf("\n---extract a field ---\n");
    uint8_t field = (uint8_t)((a >> 4) & 0x07U);
    show("(a >> 4) & 0b111 ",field);
    return 0 ;

}