#include "check_queue.h"

START_TEST(test_push_many_3)
{
    queue_t q = QUEUE_INIT;
    queue_push_many(&q, 3, 1, 2, 3);
    data_t data;
    for (size_t i = 0; i < 3; i++)
    {
        queue_pop(&q, &data);
        ck_assert_int_eq(data, i + 1);
    }
    queue_free(&q);
}
END_TEST











