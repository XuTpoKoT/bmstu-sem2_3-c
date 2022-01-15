#define _GNU_SOURCE

#include "check_film.h"

START_TEST(test_copy_uninitialised_dst)
{
    film_t src = { .title = "title1", .name = "name1", .year = 2001 }, dst = { .title = NULL, .name = NULL };
    film_t res = { .title = "title1", .name = "name1", .year = 2001 };
    ck_assert_int_eq(film_copy(&dst, &src), EXIT_SUCCESS);
    ck_assert_int_eq(film_equal(&dst, &res), true);
    film_free(&dst);
}
END_TEST

START_TEST(test_copy_initialised_dst)
{
    film_t src = { .title = "title1", .name = "name1", .year = 2001 }, dst;
    dst.title = strdup("old_title");
    dst.name = strdup("old_name");
    film_t res = { .title = "title1", .name = "name1", .year = 2001 };
    ck_assert_int_eq(film_copy(&dst, &src), EXIT_SUCCESS);
    ck_assert_int_eq(film_equal(&dst, &res), true);
    film_free(&dst);
}
END_TEST

Suite* copy_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("copy");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_copy_uninitialised_dst);
    tcase_add_test(tc_pos, test_copy_initialised_dst);

    suite_add_tcase(s, tc_pos);

    return s;
} 