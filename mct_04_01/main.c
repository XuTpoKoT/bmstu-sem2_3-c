#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int main(void)
{
    queue_t q = QUEUE_INIT;
    queue_push_many(&q, 3, 1, 2, 3);
    data_t data;
    for (size_t i = 0; i < 3; i++)
    {
        queue_pop(&q, &data);
        printf("%d\n", data);
    }
    queue_free(&q);

    return EXIT_SUCCESS;
}
