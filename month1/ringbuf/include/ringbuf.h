#ifndef RINGBUF_H
#define RINGBUF_H

#include<stdbool.h>
#include<stddef.h>
#include<stdint.h>

/*
 * a ring buffer (circular FIFO) of bytes
 * the memory is provided by the caller,so there is no malloc.
*/
typedef struct
{
    uint8_t *storage ; /*memory given by the user*/
    size_t capacity; /*total number of slots*/
    size_t head ; /*index where the next byte will be written*/
    size_t tail ; /*index where the next byte will be read */
    size_t count ; /*how many bytes are stored right now*/
}ringbuf_t;
/*prepare the ring buffer.Returns false if the buffer is invalid*/
bool ringbuf_init(ringbuf_t *rb,uint8_t *storge,size_t capacity);
/*add one byte at the end.Returns false if the buffer is full*/
bool ringbuf_push(ringbuf_t *rb,uint8_t byte);
/*remove the oldest byte and store it in *byte.Returns false if empty*/
bool ringbuf_pop(ringbuf_t *rb, uint8_t *byte);

bool ringbuf_is_empty(const ringbuf_t *rb);
bool ringbuf_is_full(const ringbuf_t *rb);
size_t ringbuf_count(const ringbuf_t *rb);

/*forget everything that is stored*/
void ringbuf_clear(ringbuf_t *rb);

#endif /*RINGBUF_H*/