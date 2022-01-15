#include "check_matrix.h"

START_TEST(test_det_one_elem)
{
    matrix_t a;
    double det, res;
    ck_assert_int_eq(matrix_create(1, 1, &a), EXIT_SUCCESS);
    a.data[0][0] = 5;
    res = 5;
    ck_assert_int_eq(matrix_det(&a, &det), EXIT_SUCCESS);
    ck_assert_double_eq(det, res);
    matrix_free(&a);
}
END_TEST

START_TEST(test_det_order_2)
{
    matrix_t a;
    double det, res;
    ck_assert_int_eq(matrix_create(2, 2, &a), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 2;
    a.data[1][0] = 3;
    a.data[1][1] = 4;
    res = -2;
    ck_assert_int_eq(matrix_det(&a, &det), EXIT_SUCCESS);
    ck_assert_double_eq(det, res);
    matrix_free(&a);
}
END_TEST

START_TEST(test_det_order_3)
{
    matrix_t a;
    double det, res;
    ck_assert_int_eq(matrix_create(3, 3, &a), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 2;
    a.data[0][2] = 3;
    a.data[1][0] = 4;
    a.data[1][1] = 5;
    a.data[1][2] = 6;
    a.data[2][0] = 7;
    a.data[2][1] = 8;
    a.data[2][2] = 9;
    res = 0.0;
    ck_assert_int_eq(matrix_det(&a, &det), EXIT_SUCCESS);
    ck_assert_double_eq(det, res);
    matrix_free(&a);
}
END_TEST

START_TEST(test_det_rows_diff_cols)
{
    matrix_t a;
    double det;
    ck_assert_int_eq(matrix_create(1, 2, &a), EXIT_SUCCESS);
    a.data[0][0] = 5;
    ck_assert_int_eq(matrix_det(&a, &det), EXIT_FAILURE);
    matrix_free(&a);
}
END_TEST

Suite* det_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("det");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_det_one_elem);
    tcase_add_test(tc_pos, test_det_order_2);
    tcase_add_test(tc_pos, test_det_order_3);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_det_rows_diff_cols);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
} 


START_TEST(test_sum_one_elem)
{
    matrix_t a, b, sum, res;
    ck_assert_int_eq(matrix_create(1, 1, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &sum), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &res), EXIT_SUCCESS);
    a.data[0][0] = 5;
    b.data[0][0] = 6;
    res.data[0][0] = 11;
    ck_assert_int_eq(matrix_sum(&a, &b, &sum), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&sum, &res), true);
    matrix_free_all(&a, &b);
    matrix_free_all(&sum, &res);
}
END_TEST

START_TEST(test_sum_one_row)
{
    matrix_t a, b, sum, res;
    ck_assert_int_eq(matrix_create(1, 3, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 3, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 3, &sum), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 3, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 2;
    a.data[0][2] = 3;
    b.data[0][0] = 6;
    b.data[0][1] = 6;
    b.data[0][2] = 6;
    res.data[0][0] = 7;
    res.data[0][1] = 8;
    res.data[0][2] = 9;
    ck_assert_int_eq(matrix_sum(&a, &b, &sum), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&sum, &res), true);
    matrix_free_all(&a, &b);
    matrix_free_all(&sum, &res);
}
END_TEST

START_TEST(test_sum_one_col)
{
    matrix_t a, b, sum, res;
    ck_assert_int_eq(matrix_create(3, 1, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(3, 1, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(3, 1, &sum), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(3, 1, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[1][0] = 2;
    a.data[2][0] = 3;
    b.data[0][0] = 6;
    b.data[1][0] = 6;
    b.data[2][0] = 6;
    res.data[0][0] = 7;
    res.data[1][0] = 8;
    res.data[2][0] = 9;
    ck_assert_int_eq(matrix_sum(&a, &b, &sum), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&sum, &res), true);
    matrix_free_all(&a, &b);
    matrix_free_all(&sum, &res);
}
END_TEST

START_TEST(test_sum_square)
{
    matrix_t a, b, sum, res;
    ck_assert_int_eq(matrix_create(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &sum), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 1;
    a.data[1][0] = 2;
    a.data[1][1] = 2;

    b.data[0][0] = -5;
    b.data[0][1] = -5;
    b.data[1][0] = 0;
    b.data[1][1] = 1;

    res.data[0][0] = -4;
    res.data[0][1] = -4;
    res.data[1][0] = 2;
    res.data[1][1] = 3;
    ck_assert_int_eq(matrix_sum(&a, &b, &sum), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&sum, &res), true);
    matrix_free_all(&a, &b);
    matrix_free_all(&sum, &res);
}
END_TEST

START_TEST(test_sum_wrong_size)
{
    matrix_t a, b, sum;
    ck_assert_int_eq(matrix_create(1, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &sum), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 2;
    b.data[0][0] = 1;
    ck_assert_int_eq(matrix_sum(&a, &b, &sum), EXIT_FAILURE);
    matrix_free_all(&a, &b);
    matrix_free(&sum);
}
END_TEST

Suite* sum_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("sum");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sum_one_elem);
    tcase_add_test(tc_pos, test_sum_one_row);
    tcase_add_test(tc_pos, test_sum_one_col);
    tcase_add_test(tc_pos, test_sum_square);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_sum_wrong_size);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
} 


START_TEST(test_mul_one_elem)
{
    matrix_t a, b, mul, res;
    ck_assert_int_eq(matrix_create(1, 1, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &mul), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &res), EXIT_SUCCESS);
    a.data[0][0] = 5;
    b.data[0][0] = 5;
    res.data[0][0] = 25;
    ck_assert_int_eq(matrix_mul(&a, &b, &mul), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&mul, &res), true);
    matrix_free_all(&a, &b);
    matrix_free_all(&mul, &res);
}
END_TEST

START_TEST(test_mul_row_and_col)
{
    matrix_t a, b, mul, res;
    ck_assert_int_eq(matrix_create(1, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 1, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &mul), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &res), EXIT_SUCCESS);
    a.data[0][0] = 2;
    a.data[0][1] = 2;
    b.data[0][0] = 3;
    b.data[1][0] = 3;
    res.data[0][0] = 12;
    ck_assert_int_eq(matrix_mul(&a, &b, &mul), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&mul, &res), true);
    matrix_free_all(&a, &b);
    matrix_free_all(&mul, &res);
}
END_TEST

START_TEST(test_mul_identity)
{
    matrix_t a, b, mul, res;
    ck_assert_int_eq(matrix_create(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &mul), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 2;
    a.data[1][0] = 3;
    a.data[1][1] = 4;

    b.data[0][0] = 1;
    b.data[0][1] = 0;
    b.data[1][0] = 0;
    b.data[1][1] = 1;

    res.data[0][0] = 1;
    res.data[0][1] = 2;
    res.data[1][0] = 3;
    res.data[1][1] = 4;
    ck_assert_int_eq(matrix_mul(&a, &b, &mul), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&mul, &res), true);
    matrix_free_all(&a, &b);
    matrix_free_all(&mul, &res);
}
END_TEST

START_TEST(test_mul_same_orders)
{
    matrix_t a, b, mul, res;
    ck_assert_int_eq(matrix_create(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &mul), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 1;
    a.data[1][0] = 3;
    a.data[1][1] = 3;

    b.data[0][0] = 2;
    b.data[0][1] = 2;
    b.data[1][0] = 2;
    b.data[1][1] = 2;

    res.data[0][0] = 4;
    res.data[0][1] = 4;
    res.data[1][0] = 12;
    res.data[1][1] = 12;
    ck_assert_int_eq(matrix_mul(&a, &b, &mul), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&mul, &res), true);
    matrix_free_all(&a, &b);
    matrix_free_all(&mul, &res);
}
END_TEST

START_TEST(test_mul_wrong_size)
{
    matrix_t a, b, mul;
    ck_assert_int_eq(matrix_create(1, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &mul), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 2;
    b.data[0][0] = 1;
    ck_assert_int_eq(matrix_mul(&a, &b, &mul), EXIT_FAILURE);
    matrix_free_all(&a, &b);
    matrix_free(&mul);
}
END_TEST

Suite* mul_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("mul");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_mul_one_elem);
    tcase_add_test(tc_pos, test_mul_row_and_col);
    tcase_add_test(tc_pos, test_mul_identity);
    tcase_add_test(tc_pos, test_mul_same_orders);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_mul_wrong_size);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
} 


START_TEST(test_pow_one_elem)
{
    matrix_t a, res;
    ck_assert_int_eq(matrix_create(1, 1, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &res), EXIT_SUCCESS);
    a.data[0][0] = 5;
    res.data[0][0] = 5;
    ck_assert_int_eq(matrix_pow(&a, 1), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &res);
}
END_TEST

START_TEST(test_pow_power_0)
{
    matrix_t a, res;
    ck_assert_int_eq(matrix_create(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 2;
    a.data[1][0] = 3;
    a.data[1][1] = 4;

    res.data[0][0] = 1;
    res.data[0][1] = 0;
    res.data[1][0] = 0;
    res.data[1][1] = 1;
    ck_assert_int_eq(matrix_pow(&a, 0), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &res);
}
END_TEST

START_TEST(test_pow_power_1)
{
    matrix_t a, res;
    ck_assert_int_eq(matrix_create(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 2;
    a.data[1][0] = 3;
    a.data[1][1] = 4;

    res.data[0][0] = 1;
    res.data[0][1] = 2;
    res.data[1][0] = 3;
    res.data[1][1] = 4;
    ck_assert_int_eq(matrix_pow(&a, 1), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &res);
}
END_TEST

START_TEST(test_pow_power_2)
{
    matrix_t a, res;
    ck_assert_int_eq(matrix_create(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 1;
    a.data[1][0] = 2;
    a.data[1][1] = 2;

    res.data[0][0] = 3;
    res.data[0][1] = 3;
    res.data[1][0] = 6;
    res.data[1][1] = 6;
    ck_assert_int_eq(matrix_pow(&a, 2), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &res);
}
END_TEST

START_TEST(test_pow_power_3)
{
    matrix_t a, res;
    ck_assert_int_eq(matrix_create(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 1;
    a.data[1][0] = 2;
    a.data[1][1] = 2;

    res.data[0][0] = 9;
    res.data[0][1] = 9;
    res.data[1][0] = 18;
    res.data[1][1] = 18;
    ck_assert_int_eq(matrix_pow(&a, 3), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &res);
}
END_TEST

START_TEST(test_pow_rows_diff_cols)
{
    matrix_t a;
    ck_assert_int_eq(matrix_create(1, 2, &a), EXIT_SUCCESS);

    ck_assert_int_eq(matrix_pow(&a, 1), EXIT_FAILURE);

    matrix_free(&a);
}
END_TEST

Suite* pow_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("pow");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_pow_one_elem);
    tcase_add_test(tc_pos, test_pow_power_0);
    tcase_add_test(tc_pos, test_pow_power_1);
    tcase_add_test(tc_pos, test_pow_power_2);
    tcase_add_test(tc_pos, test_pow_power_3);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_pow_rows_diff_cols);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
} 