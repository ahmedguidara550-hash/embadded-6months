#include "ringbuf.h"

bool ringbuf_init(ringbuf_t *rb,uint8_t *storage,size_t capacity){
    if ((rb==NULL)|| (storage == NULL) || (capacity == 0U)){
        return false;
    }
    rb ->storage =storage;
    rb ->capacity = capacity;
    rb ->head = 0U;
    rb ->tail =0U;
    rb ->count = 0U;
    return true;
}

bool ringbuf_push(ringbuf_t *rb,uint8_t byte){
    if ((rb == NULL)||(ringbuf_is_full(rb)))
    {
        return false;
    }
    rb ->storage[rb ->head] = byte;
    rb ->head = (rb->head + 1U) % rb ->capacity ;
    rb ->count++;
    return true;
}

bool ringbuf_pop(ringbuf_t *rb,uint8_t *byte){
    if ((rb == NULL) || (byte == NULL) || ringbuf_is_empty(rb))
    {
        return false;
    }
    *byte = rb ->storage[rb->tail];
    rb->tail = (rb->tail + 1U) % rb->capacity;
    rb ->count--;
    return true;
}
bool ringbuf_is_empty(const ringbuf_t *rb){
    return (rb == NULL) || (rb->count == 0U);
}
bool ringbuf_is_full(const ringbuf_t *rb){
    return (rb == NULL) || (rb->count == rb ->capacity);
}

size_t ringbuf_count(const ringbuf_t *rb){
    return (rb == NULL) ? 0U : rb->count;
}

void ringbuf_clear(ringbuf_t *rb){
    if (rb != NULL)
    {
        rb->head = 0U;
        rb->tail = 0U;
        rb->count = 0U;
    }
    
}