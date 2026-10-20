#include "unity.h"
#include "ringbuf.h"

#define CAPACITY 4U

static uint8_t memory[CAPACITY];
static ringbuf_t rb;

/*Unity calls setUp() before every test and tearDown() after it*/
void setUp(void){
    (void)ringbuf_init(&rb,memory,CAPACITY);
}
void tearDown(void){
}

void test_init_rejects_bad_arguments(void){
    ringbuf_t other ;
    TEST_ASSERT_FALSE(ringbuf_init(NULL,memory,CAPACITY));
    TEST_ASSERT_FALSE(ringbuf_init(&other,NULL,CAPACITY));
    TEST_ASSERT_FALSE(ringbuf_init(&other,memory,0U));
}
void test_new_buffer_is_empty(void){
    TEST_ASSERT_TRUE(ringbuf_is_empty(&rb));
    TEST_ASSERT_FALSE(ringbuf_is_full(&rb));
    TEST_ASSERT_EQUAL_UINT32(0U,ringbuf_count(&rb));
}
void test_push_then_pop_returns_same_byte(void){
    uint8_t out = 0;
    TEST_ASSERT_TRUE(ringbuf_push(&rb,0x5A));
    TEST_ASSERT_EQUAL_UINT32(1U,ringbuf_count(&rb));
    TEST_ASSERT_TRUE(ringbuf_pop(&rb,&out));
    TEST_ASSERT_EQUAL_HEX8(0x5A,out);
    TEST_ASSERT_TRUE(ringbuf_is_empty(&rb));
}
void test_bytes_come_out_in_the_order_they_went_in(void)
{
    uint8_t out = 0;
    (void)ringbuf_push(&rb, 1);
    (void)ringbuf_push(&rb, 2);
    (void)ringbuf_push(&rb, 3);
 
    (void)ringbuf_pop(&rb, &out);
    TEST_ASSERT_EQUAL_UINT8(1, out);
    (void)ringbuf_pop(&rb, &out);
    TEST_ASSERT_EQUAL_UINT8(2, out);
    (void)ringbuf_pop(&rb, &out);
    TEST_ASSERT_EQUAL_UINT8(3, out);
}
 
void test_buffer_becomes_full_and_rejects_push(void)
{
    for (uint8_t i = 0; i < CAPACITY; i++)
    {
        TEST_ASSERT_TRUE(ringbuf_push(&rb, i));
    }
    TEST_ASSERT_TRUE(ringbuf_is_full(&rb));
    TEST_ASSERT_FALSE(ringbuf_push(&rb, 99));
    TEST_ASSERT_EQUAL_UINT32(CAPACITY, ringbuf_count(&rb));
}
void test_pop_on_empty_buffer_fails_and_keeps_output_unchanged(void)
{
    uint8_t out = 0xEE;
    TEST_ASSERT_FALSE(ringbuf_pop(&rb, &out));
    TEST_ASSERT_EQUAL_HEX8(0xEE, out);
}
 
void test_wrap_around_keeps_working(void)
{
    uint8_t out = 0;
 
    /* Fill, then empty half, then add more so that head wraps to index 0. */
    for (uint8_t i = 1; i <= CAPACITY; i++)
    {
        (void)ringbuf_push(&rb, i);          /* 1 2 3 4 */
    }
    (void)ringbuf_pop(&rb, &out);            /* removes 1 */
    (void)ringbuf_pop(&rb, &out);            /* removes 2 */
    TEST_ASSERT_TRUE(ringbuf_push(&rb, 5));  /* goes to index 0 */
    TEST_ASSERT_TRUE(ringbuf_push(&rb, 6));  /* goes to index 1 */
    TEST_ASSERT_TRUE(ringbuf_is_full(&rb));
 
    uint8_t expected[] = {3, 4, 5, 6};
    for (size_t i = 0; i < sizeof(expected); i++)
    {
        TEST_ASSERT_TRUE(ringbuf_pop(&rb, &out));
        TEST_ASSERT_EQUAL_UINT8(expected[i], out);
    }
    TEST_ASSERT_TRUE(ringbuf_is_empty(&rb));
}
 
void test_clear_empties_the_buffer(void)
{
    (void)ringbuf_push(&rb, 1);
    (void)ringbuf_push(&rb, 2);
    ringbuf_clear(&rb);
    TEST_ASSERT_TRUE(ringbuf_is_empty(&rb));
    TEST_ASSERT_EQUAL_UINT32(0U, ringbuf_count(&rb));
}
 
void test_null_pointers_are_handled_safely(void)
{
    uint8_t out = 0;
    TEST_ASSERT_FALSE(ringbuf_push(NULL, 1));
    TEST_ASSERT_FALSE(ringbuf_pop(NULL, &out));
    TEST_ASSERT_FALSE(ringbuf_pop(&rb, NULL));
    TEST_ASSERT_TRUE(ringbuf_is_empty(NULL));
    TEST_ASSERT_TRUE(ringbuf_is_full(NULL));
    TEST_ASSERT_EQUAL_UINT32(0U, ringbuf_count(NULL));
    ringbuf_clear(NULL);  /* must simply not crash */
}

void test_free_space_is_capacity_minus_count(void){
    TEST_ASSERT_EQUAL_UINT32(CAPACITY,ringbuf_free_space(&rb));
    (void)ringbuf_push(&rb,1);
    TEST_ASSERT_EQUAL_UINT32(CAPACITY - 1U , ringbuf_free_space(&rb));
    TEST_ASSERT_EQUAL_UINT32(0U,ringbuf_free_space(NULL));
}
 
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_rejects_bad_arguments);
    RUN_TEST(test_new_buffer_is_empty);
    RUN_TEST(test_push_then_pop_returns_same_byte);
    RUN_TEST(test_bytes_come_out_in_the_order_they_went_in);
    RUN_TEST(test_buffer_becomes_full_and_rejects_push);
    RUN_TEST(test_pop_on_empty_buffer_fails_and_keeps_output_unchanged);
    RUN_TEST(test_wrap_around_keeps_working);
    RUN_TEST(test_clear_empties_the_buffer);
    RUN_TEST(test_null_pointers_are_handled_safely);
    RUN_TEST(test_free_space_is_capacity_minus_count);
    return UNITY_END();
}
