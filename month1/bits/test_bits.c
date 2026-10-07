#include<assert.h>
#include<stdio.h>
#include "bits.h"

int main(){
    uint32_t reg = 0 ;
    SET_BIT(reg,3);
    assert(reg == 0x08U);
    SET_BIT(reg,0);
    assert(reg == 0x09U);
    TOGGLE_BIT(reg,5);
    assert (reg == 0x29U);
    CLEAR_BIT(reg,3);
    assert(reg == 0x21U);
    assert(READ_BIT(reg,5)==1U);
    assert(READ_BIT(reg,4)==0U);
    assert(bits_get_field(0xCAU,4,3) == 4U);
    assert(bits_get_field(0xFFFFFFFFU,0,32) == 0xFFFFFFFFU);
    assert(bits_swap16(0x1234U) == 0x3412U);
    assert(bits_count_ones(0U) == 0U);
    assert(bits_count_ones(0xFFU) == 8U);
    assert(bits_count_ones(0xCAU) ==4U);
    assert(!bits_parity_odd(0xCAU));
    assert(bits_parity_odd(0x07U));
    assert(bits_set_field(0xFFU,4,2,2U) == 0xEFU);
    assert(bits_set_field(0x00U,0,8,0xABU) == 0xABU);
    assert(bits_set_field(0xFFFFFFFF,0,32,0U) == 0U);

    printf("all bits.h tests passed!\n");
    return 0;
}