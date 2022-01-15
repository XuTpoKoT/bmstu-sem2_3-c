#include "check_arr.h"

START_TEST(test_mysort_zero_elems)
{
    int arr[] = { 1 };
    size_t cnt_elems = 0;

    mysort(arr, cnt_elems, sizeof(int), compare_int);
}
END_TEST

START_TEST(test_mysort_one_elem)
{
    int arr[] = { 1 };
    size_t cnt_elems = 1;
    int res[] = { 1 };

    mysort(arr, cnt_elems, sizeof(int), compare_int);
    for (size_t i = 0; i < cnt_elems; i++)
        ck_assert_int_eq(arr[i], res[i]);
}
END_TEST

START_TEST(test_mysort_sorted)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    size_t cnt_elems = 5;
    int res[] = { 1, 2, 3, 4, 5 };

    mysort(arr, cnt_elems, sizeof(int), compare_int);
    for (size_t i = 0; i < 5; i++)
        ck_assert_int_eq(arr[i], res[i]);
}
END_TEST

START_TEST(test_mysort_unsorted)
{
    int arr[] = { 5, 4, 3, 2, 1 };
    size_t cnt_elems = 5;
    int res[] = { 1, 2, 3, 4, 5 };

    mysort(arr, cnt_elems, sizeof(int), compare_int);
    for (size_t i = 0; i < cnt_elems; i++)
        ck_assert_int_eq(arr[i], res[i]);
}
END_TEST

START_TEST(test_mysort_random)
{
    int arr[] = { 4, 1, 3, 2, 5 };
    size_t cnt_elems = 5;
    int res[] = { 1, 2, 3, 4, 5 };

    mysort(arr, cnt_elems, sizeof(int), compare_int);
    for (size_t i = 0; i < cnt_elems; i++)
        ck_assert_int_eq(arr[i], res[i]);
}
END_TEST


START_TEST(test_mysort_same)
{
    int arr[] = { 4, 4, 4, 4, 4 };
    size_t cnt_elems = 5;
    int res[] = { 4, 4, 4, 4, 4 };

    mysort(arr, cnt_elems, sizeof(int), compare_int);
    for (size_t i = 0; i < cnt_elems; i++)
        ck_assert_int_eq(arr[i], res[i]);
}
END_TEST

START_TEST(test_mysort_double)
{
    double arr[] = { 4, 1, 3, 2, 5 };
    size_t cnt_elems = 5;
    double res[] = { 1, 2, 3, 4, 5 };

    mysort(arr, cnt_elems, sizeof(double), compare_double);
    for (size_t i = 0; i < cnt_elems; i++)
        ck_assert_double_eq(arr[i], res[i]);
}
END_TEST

Suite* mysort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("mysort");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_mysort_zero_elems);
    tcase_add_test(tc_pos, test_mysort_one_elem);
    tcase_add_test(tc_pos, test_mysort_sorted);
    tcase_add_test(tc_pos, test_mysort_unsorted);
    tcase_add_test(tc_pos, test_mysort_random);
    tcase_add_test(tc_pos, test_mysort_same);
    tcase_add_test(tc_pos, test_mysort_double);
    suite_add_tcase(s, tc_pos);

    return s;
}



START_TEST(test_key_without_neg)
{
    int arr[] = { 1, 2, 3 };
    size_t src_elems = 3, dst_elems = 3;
    int tmp[3];
    int res[] = { 1, 2, 3 };
    int *pb_dst = NULL, *pe_dst;

    int rc = key(arr, arr + src_elems, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < dst_elems; i++)
        tmp[i] = pb_dst[i];
    free(pb_dst);

    for (size_t i = 0; i < dst_elems; i++)
        ck_assert_int_eq(tmp[i], res[i]);
}
END_TEST

START_TEST(test_key_last_neg)
{
    int arr[] = { 1, 2, 3, -5 };
    size_t src_elems = 4, dst_elems = 3;
    int tmp[3];
    int res[] = { 1, 2, 3 };
    int *pb_dst = NULL, *pe_dst;

    int rc = key(arr, arr + src_elems, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < dst_elems; i++)
        tmp[i] = pb_dst[i];
    free(pb_dst);

    for (size_t i = 0; i < dst_elems; i++)
        ck_assert_int_eq(tmp[i], res[i]);
}
END_TEST

START_TEST(test_key_mid_neg)
{
    int arr[] = { 1, 2, 3, -4, 5, 6 };
    size_t src_elems = 6, dst_elems = 3;
    int tmp[3];
    int res[] = { 1, 2, 3 };
    int *pb_dst = NULL, *pe_dst;

    int rc = key(arr, arr + src_elems, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < dst_elems; i++)
        tmp[i] = pb_dst[i];
    free(pb_dst);

    for (size_t i = 0; i < dst_elems; i++)
        ck_assert_int_eq(tmp[i], res[i]);
}
END_TEST

START_TEST(test_key_many_neg)
{
    int arr[] = { 1, -2, 3, -4, 5, -6, 7 };
    size_t src_elems = 7, dst_elems = 5;
    int tmp[5];
    int res[] = { 1, -2, 3, -4, 5 };
    int *pb_dst = NULL, *pe_dst;

    int rc = key(arr, arr + src_elems, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, EXIT_SUCCESS);
    for (size_t i = 0; i < dst_elems; i++)
        tmp[i] = pb_dst[i];
    free(pb_dst);

    for (size_t i = 0; i < dst_elems; i++)
        ck_assert_int_eq(tmp[i], res[i]);
}
END_TEST

START_TEST(test_key_first_neg)
{
    int arr[] = { -1 };
    size_t src_elems = 1;
    int *pb_dst = NULL, *pe_dst;

    int rc = key(arr, arr + src_elems, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, EXIT_FAILURE);
}
END_TEST


START_TEST(test_key_null_ptr)
{
    int arr[] = { 1 };
    size_t src_elems = 1;
    int *pb_dst = NULL, *pe_dst;

    int rc = key(NULL, arr + src_elems, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, EXIT_FAILURE);
}
END_TEST

Suite* key_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("key");      

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_key_without_neg);
    tcase_add_test(tc_pos, test_key_last_neg);
    tcase_add_test(tc_pos, test_key_mid_neg);
    tcase_add_test(tc_pos, test_key_many_neg);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_key_first_neg);
    tcase_add_test(tc_neg, test_key_null_ptr);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);
    
    return s;
} 
    