#include "check_sparse_matr.h"

START_TEST(test_smatr_sum_one_elem)
{
    matr_t a, b, res;
    ck_assert_int_eq(matr_malloc(1, 1, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(1, 1, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(1, 1, &res), EXIT_SUCCESS);
    a.data[0][0] = 5;
    b.data[0][0] = 6;
    res.data[0][0] = 11;
    sparse_matr_t *sa = matr_to_sparse_matr(&a);
    sparse_matr_t *sb = matr_to_sparse_matr(&b);
    sparse_matr_t *sres = matr_to_sparse_matr(&res);
    sparse_matr_t *ssum = sparse_matr_sum(sa, sb);
    ck_assert_int_eq(sparse_matr_equal(ssum, sres), true);
    matr_free_two(&a, &b);
    matr_free(&res);
    sparse_matr_free_two(&sa, &sb);
    sparse_matr_free_two(&sres, &ssum);
}
END_TEST

START_TEST(test_smatr_sum_one_row)
{
    matr_t a, b, res;
    ck_assert_int_eq(matr_malloc(1, 3, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(1, 3, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(1, 3, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[0][1] = 2;
    a.data[0][2] = 3;
    b.data[0][0] = 6;
    b.data[0][1] = 6;
    b.data[0][2] = 6;
    res.data[0][0] = 7;
    res.data[0][1] = 8;
    res.data[0][2] = 9;
    sparse_matr_t *sa = matr_to_sparse_matr(&a);
    sparse_matr_t *sb = matr_to_sparse_matr(&b);
    sparse_matr_t *sres = matr_to_sparse_matr(&res);
    sparse_matr_t *ssum = sparse_matr_sum(sa, sb);
    ck_assert_int_eq(sparse_matr_equal(ssum, sres), true);
    matr_free_two(&a, &b);
    matr_free(&res);
    sparse_matr_free_two(&sa, &sb);
    sparse_matr_free_two(&sres, &ssum);
}
END_TEST

START_TEST(test_smatr_sum_one_col)
{
    matr_t a, b, res;
    ck_assert_int_eq(matr_malloc(3, 1, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(3, 1, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(3, 1, &res), EXIT_SUCCESS);
    a.data[0][0] = 1;
    a.data[1][0] = 2;
    a.data[2][0] = 3;
    b.data[0][0] = 6;
    b.data[1][0] = 6;
    b.data[2][0] = 6;
    res.data[0][0] = 7;
    res.data[1][0] = 8;
    res.data[2][0] = 9;
    sparse_matr_t *sa = matr_to_sparse_matr(&a);
    sparse_matr_t *sb = matr_to_sparse_matr(&b);
    sparse_matr_t *sres = matr_to_sparse_matr(&res);
    sparse_matr_t *ssum = sparse_matr_sum(sa, sb);
    ck_assert_int_eq(sparse_matr_equal(ssum, sres), true);
    matr_free_two(&a, &b);
    matr_free(&res);
    sparse_matr_free_two(&sa, &sb);
    sparse_matr_free_two(&sres, &ssum);
}
END_TEST

START_TEST(test_smatr_sum_square)
{
    matr_t a, b, res;
    ck_assert_int_eq(matr_malloc(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(2, 2, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(2, 2, &res), EXIT_SUCCESS);
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
    sparse_matr_t *sa = matr_to_sparse_matr(&a);
    sparse_matr_t *sb = matr_to_sparse_matr(&b);
    sparse_matr_t *sres = matr_to_sparse_matr(&res);
    sparse_matr_t *ssum = sparse_matr_sum(sa, sb);
    ck_assert_int_eq(sparse_matr_equal(ssum, sres), true);
    matr_free_two(&a, &b);
    matr_free(&res);
    sparse_matr_free_two(&sa, &sb);
    sparse_matr_free_two(&sres, &ssum);
}
END_TEST

Suite* smatr_sum_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sparse matrix sum");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_smatr_sum_one_elem);
    tcase_add_test(tc_pos, test_smatr_sum_one_row);
    tcase_add_test(tc_pos, test_smatr_sum_one_col);
    tcase_add_test(tc_pos, test_smatr_sum_square);

    suite_add_tcase(s, tc_pos);

    return s;
} 


START_TEST(test_smatr_mul_one_elem)
{
    matr_t a, b, res;
    ck_assert_int_eq(matr_malloc(1, 1, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(1, 1, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(1, 1, &res), EXIT_SUCCESS);
    a.data[0][0] = 5;
    b.data[0][0] = 5;
    res.data[0][0] = 25;
    sparse_matr_t *sa = matr_to_sparse_matr(&a);
    sparse_matr_t *sb = matr_to_sparse_matr(&b);
    sparse_matr_t *sres = matr_to_sparse_matr(&res);
    sparse_matr_t *smul = sparse_matr_mul(sa, sb);
    ck_assert_int_eq(sparse_matr_equal(smul, sres), true);
    matr_free_two(&a, &b);
    matr_free(&res);
    sparse_matr_free_two(&sa, &sb);
    sparse_matr_free_two(&sres, &smul);
}
END_TEST

START_TEST(test_smatr_mul_row_and_col)
{
    matr_t a, b, res;
    ck_assert_int_eq(matr_malloc(1, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(2, 1, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(1, 1, &res), EXIT_SUCCESS);
    a.data[0][0] = 2;
    a.data[0][1] = 2;
    b.data[0][0] = 3;
    b.data[1][0] = 3;
    res.data[0][0] = 12;
    sparse_matr_t *sa = matr_to_sparse_matr(&a);
    sparse_matr_t *sb = matr_to_sparse_matr(&b);
    sparse_matr_t *sres = matr_to_sparse_matr(&res);
    sparse_matr_t *smul = sparse_matr_mul(sa, sb);
    ck_assert_int_eq(sparse_matr_equal(smul, sres), true);
    matr_free_two(&a, &b);
    matr_free(&res);
    sparse_matr_free_two(&sa, &sb);
    sparse_matr_free_two(&sres, &smul);
}
END_TEST

START_TEST(test_smatr_mul_identity)
{
    matr_t a, b, res;
    ck_assert_int_eq(matr_malloc(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(2, 2, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(2, 2, &res), EXIT_SUCCESS);
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
    sparse_matr_t *sa = matr_to_sparse_matr(&a);
    sparse_matr_t *sb = matr_to_sparse_matr(&b);
    sparse_matr_t *sres = matr_to_sparse_matr(&res);
    sparse_matr_t *smul = sparse_matr_mul(sa, sb);
    ck_assert_int_eq(sparse_matr_equal(smul, sres), true);
    matr_free_two(&a, &b);
    matr_free(&res);
    sparse_matr_free_two(&sa, &sb);
    sparse_matr_free_two(&sres, &smul);
}
END_TEST

START_TEST(test_smatr_mul_same_orders)
{
    matr_t a, b, res;
    ck_assert_int_eq(matr_malloc(2, 2, &a), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(2, 2, &b), EXIT_SUCCESS);
    ck_assert_int_eq(matr_malloc(2, 2, &res), EXIT_SUCCESS);
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
    sparse_matr_t *sa = matr_to_sparse_matr(&a);
    sparse_matr_t *sb = matr_to_sparse_matr(&b);
    sparse_matr_t *sres = matr_to_sparse_matr(&res);
    sparse_matr_t *smul = sparse_matr_mul(sa, sb);
    ck_assert_int_eq(sparse_matr_equal(smul, sres), true);
    matr_free_two(&a, &b);
    matr_free(&res);
    sparse_matr_free_two(&sa, &sb);
    sparse_matr_free_two(&sres, &smul);
}
END_TEST

Suite* smatr_mul_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sparse matrix mul");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_smatr_mul_one_elem);
    tcase_add_test(tc_pos, test_smatr_mul_row_and_col);
    tcase_add_test(tc_pos, test_smatr_mul_identity);
    tcase_add_test(tc_pos, test_smatr_mul_same_orders);

    suite_add_tcase(s, tc_pos);

    return s;
} 

