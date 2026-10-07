#ifndef BITS_H
#define BITS_H 
#include<stdint.h>
#include<stdbool.h>

/*A mask with only bit n set.*/
#define BIT(n) (1U << (n))
/*work on a variable "reg"(must be a real variable,not a number)*/
#define SET_BIT(reg,n) ((reg) |= BIT(n))
#define CLEAR_BIT(reg,n) ((reg) &= ~BIT(n))
#define TOGGLE_BIT(reg,n) ((reg) ^= BIT(n))
#define READ_BIT(reg,n) (((reg) >> (n)) & 1U )

/*extract "width" bits starting at bit "pos".*/
static inline uint32_t bits_get_field(uint32_t value,uint32_t pos,uint32_t width){
    uint32_t mask = (width >= 32U) ? 0xFFFFFFFFU : ((1U << width) - 1U);
    return (value >> pos) & mask ;
}
static inline uint32_t bits_set_field(uint32_t value,uint32_t pos,uint32_t width,uint32_t field){
    uint32_t mask = (width >= 32U) ? 0xFFFFFFFFU : ((1U << width) - 1U);
    return (value & ~(mask << pos)) | ((field & mask) << pos);
}
/*Swap the the two bytes of a 16-bit value : 0x1234 -> 0x3412*/
static inline uint16_t bits_swap16(uint16_t value){
    return (uint16_t)((value << 8) | (value >> 8));
}
/*counts how many bits are 1 .*/
static inline uint32_t bits_count_ones(uint32_t value){
    uint32_t count = 0;
    while (value != 0U)
    {
        count += (value & 1U);
        value >>= 1;
    }
    return count;
    
}
/*true when the number of 1-bits is odd*/
static inline bool bits_parity_odd(uint32_t value){
    return(bits_count_ones(value) % 2U )==1U ;
}

#endif /*BITS_H*/