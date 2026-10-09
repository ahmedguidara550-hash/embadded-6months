#include<stdio.h>
#include<stdint.h>

typedef struct {
    uint8_t a; /*1 byte*/
    uint32_t b; /*4 byte*/
    uint8_t c;  /*1 byte*/   
}messy_t;
typedef struct{
    uint32_t b ;
    uint8_t a;
    uint8_t c;
}tidy_t;
typedef struct __attribute((packed)){
    uint8_t a;
    uint32_t b;
    uint8_t c;
}packed_t;

int main(){
    printf("fields add up to : %d bytes\n",1+4+1);
    printf("sizeof(messy_t) : %zu\n",sizeof(messy_t));
    printf("sizeof(tidy_t) : %zu\n",sizeof(tidy_t));
    printf("sizeof(packed_t) : %zu\n",sizeof(packed_t));
    return 0;
}