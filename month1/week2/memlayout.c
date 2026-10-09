#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

int global_with_value = 42; /*goes to .data*/
int global_without_value ;  /*goes to .bss*/
const int read_only_number ; /*goes to .rodata*/
char big_buffer[1000]={1};

void show_stack_address(void){
    int local_in_function = 1;
    printf("local in function : %p\n",(void *)&local_in_function);
}

int main(void){
    static int static_counter = 5 ;/*goes to .data*/
    int local_in_main = 3;       /*stack*/
    int *on_heap = malloc(sizeof(int));  /*heap*/

    printf("code main :%p\n",(void *)main);
    printf("read_only_number : %p\n",(void *)&read_only_number);
    printf("global_with_value : %p\n",(void *)&global_with_value);
    printf("static_counter : %p\n",(void *)&static_counter);
    printf("global without value : %p\n",(void *)&global_without_value);
    printf("heap malloc : %p\n",(void *)on_heap);
    printf("local in main : %p\n",(void *)&local_in_main);
    show_stack_address();
    free(on_heap);
    return 0;
}