#include "check_matrix.h"

START_TEST(test_trunc_to_square_one_elem)
{
    matrix_t a, res;
    ck_assert_int_eq(matrix_create(1, 1, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    res.data[0][0] = 1;
    matrix_trunc_to_square(&a);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &res);
}
END_TEST

START_TEST(test_trunc_to_square_square)
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
    matrix_trunc_to_square(&a);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &res);
}
END_TEST

START_TEST(test_trunc_to_square_del_row)
{
    matrix_t a, res;
    ck_assert_int_eq(matrix_create(3, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 8;
    a.data[1][0] = 3;
    a.data[1][1] = 1;
    a.data[2][0] = 2;
    a.data[2][1] = 5;
    res.data[0][0] = 3;
    res.data[0][1] = 1;
    res.data[1][0] = 2;
    res.data[1][1] = 5;
    matrix_trunc_to_square(&a);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &res);
}
END_TEST

START_TEST(test_trunc_to_square_del_col)
{
    matrix_t a, res;
    ck_assert_int_eq(matrix_create(2, 3, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &res), EXIT_SUCCESS);
    a.data[0][0] = 4;
    a.data[0][1] = -8;
    a.data[0][2] = 4;
    a.data[1][0] = 4;
    a.data[1][1] = 5;
    a.data[1][2] = -8;
    res.data[0][0] = 4;
    res.data[0][1] = 4;
    res.data[1][0] = 4;
    res.data[1][1] = -8;
    matrix_trunc_to_square(&a);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &res);
}
END_TEST

Suite* trunc_to_square_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("trunc_to_square");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_trunc_to_square_one_elem);
    tcase_add_test(tc_pos, test_trunc_to_square_square);
    tcase_add_test(tc_pos, test_trunc_to_square_del_row);
    tcase_add_test(tc_pos, test_trunc_to_square_del_col);
    suite_add_tcase(s, tc_pos);

    return s;
}


START_TEST(test_make_sym_size_one_elem)
{
    matrix_t a, b,res;
    ck_assert_int_eq(matrix_create(1, 1, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(1, 1, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    b.data[0][0] = 2;
    res.data[0][0] = 1;
    ck_assert_int_eq(matrix_make_sym_size(&a, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &b);
    matrix_free(&res);
}
END_TEST

START_TEST(test_make_sym_size_same_orders)
{
    matrix_t a, b,res;
    ck_assert_int_eq(matrix_create(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(2, 2, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 2;
    a.data[1][0] = 3;
    a.data[1][1] = 4;
    b.data[0][0] = 2;
    b.data[0][1] = 2;
    b.data[1][0] = 3;
    b.data[1][1] = 3;
    res.data[0][0] = 1;
    res.data[0][1] = 2;
    res.data[1][0] = 3;
    res.data[1][1] = 4;
    ck_assert_int_eq(matrix_make_sym_size(&a, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &b);
    matrix_free(&res);
}
END_TEST

START_TEST(test_make_sym_size_usual)
{
    matrix_t a, b,res;
    ck_assert_int_eq(matrix_create(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(3, 3, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_create(3, 3, &res), EXIT_SUCCESS);
    a.data[0][0] = 4;
    a.data[0][1] = 7;
    a.data[1][0] = 3;
    a.data[1][1] = 2;

    b.data[0][0] = 1;
    b.data[0][1] = 2;
    b.data[0][2] = 3;
    b.data[1][0] = 4;
    b.data[1][1] = 5;
    b.data[1][2] = 6;
    b.data[2][0] = 7;
    b.data[2][1] = 8;
    b.data[2][2] = 9;

    res.data[0][0] = 4;
    res.data[0][1] = 7;
    res.data[0][2] = 7;
    res.data[1][0] = 3;
    res.data[1][1] = 2;
    res.data[1][2] = 3;
    res.data[2][0] = 3;
    res.data[2][1] = 3;
    res.data[2][2] = 3;
    ck_assert_int_eq(matrix_make_sym_size(&a, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matrix_equal(&a, &res), true);
    matrix_free_all(&a, &b);
    matrix_free(&res);
}
END_TEST

Suite* make_sym_size_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("make_sym_size");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_make_sym_size_one_elem);
    tcase_add_test(tc_pos, test_make_sym_size_same_orders);
    tcase_add_test(tc_pos, test_make_sym_size_usual);
    suite_add_tcase(s, tc_pos);

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

START_TEST(test_mul_wrong_orders)
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
    tcase_add_test(tc_neg, test_mul_wrong_orders);

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