#include<stdio.h>
#include<stdint.h>

typedef struct {
    uint8_t id;
    uint16_t temp_x10;
    uint8_t flags ;
} sensor_t;

void double_it_wrong(int x){
    x = x * 2;
}
void double_it_right(int *x){
    *x *=2;
}

int main (){
    /*arrays*/
    int scores[5] = {10,20,30,40,50};
    printf("scores[0] = %d , scores[4] = %d",scores[0],scores[4]);
    /*variables live at address*/
    int age = 25;
    int *p = &age;
    printf("value of age : %d\n",age);
    printf("size of an int : %zu bytes\n",sizeof(age));
    printf("*p (value at p) : %d\n",*p);
    *p = 26;
    printf("after *p =26 , age =%d\n",age);
    /*by value vs by address*/
    int n = 5;
    double_it_wrong(n);
    printf("after double_it_wrong : n = %d\n",n);
    double_it_right(&n);
    printf("after double it right : n = %d\n",n);
    /*arrays and pointers are cousins*/
    int *q = scores;
    printf("q[2] = %d\n",q[2]);
    printf("*(q+2) = %d\n",*(q+2));
    printf("distance between scores[1] and scores[0] = %td bytes\n",(char *)&scores[1] - (char *)&scores[0]);
    /*loop over an array*/
    int total = 0;
    for (int i = 0;i<5;i++){
        total +=scores[i];
    }
    printf("total =%d\n",total);
    /*struct*/
    sensor_t s = {.id=7,.temp_x10=253,.flags=0x01};
    sensor_t *ps = &s;
    printf("sensor %u : %u.%u c ,flags=0x%02X\n",(unsigned)s.id,(unsigned)(s.temp_x10 / 10),(unsigned)(s.temp_x10 % 10),(unsigned)s.flags);
    ps -> temp_x10 = 301;
    printf("via pointer : %u.%u C\n",(unsigned)(s.temp_x10 / 10),(unsigned)(s.temp_x10 % 10));
    printf("sizeof(sensor_t) = %zu\n",sizeof(sensor_t));
    /* a c string is an array of char ending with 0*/
    char word[] = "ARM";
    printf("word has %zu bytes :",sizeof(word));
    for (size_t i = 0;i < sizeof(word);i++){
        printf("%d",word[i]);
    }
    printf("\n");
    return 0 ;
}
