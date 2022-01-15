#include <limits.h>

#include "check_my_snprintf.h"
#include "mystring.h"

START_TEST(test_snprintf_one_char)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    char c = 'a';
    const char *format = "%c";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, c), snprintf(s2, MYSTRING_LEN, format, c));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_chars)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    char c1 = 'a';
    char c2 = 'Q';
    char c3 = 'v';
    const char *format = "%c %c%c";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, c1, c2, c3), snprintf(s2, MYSTRING_LEN, format, c1, c2, c3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_string)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    char *s3 = "Dima";
    const char *format = "%s";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, s3), snprintf(s2, MYSTRING_LEN, format, s3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_strings)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    char *s3 = "qwe qe 56";
    char *s4 = "  ";
    char *s5 = "";
    const char *format = " %s%s%s";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, s3, s4, s5), snprintf(s2, MYSTRING_LEN, format, s3, s4, s5));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_int)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    int x = 0;
    const char *format = "%i";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_ints)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    int x1 = 0;
    int x2 = -12345;
    int x3 = 14;
    const char *format = "%i %i%i";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_min_int)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    int x = INT_MIN;
    const char *format = "%i";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_int)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    int x = INT_MAX;
    const char *format = "%i";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_short_int)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    short x = 0;
    const char *format = "%hi";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_short_ints)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    short x1 = 0;
    short x2 = -12345;
    short x3 = 14;
    const char *format = "%hi %hi%hi";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_min_short_int)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    short x = SHRT_MIN;
    const char *format = "%hi";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_short_int)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    short x = SHRT_MAX;
    const char *format = "%hi";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_long_int)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    long x = 0;
    const char *format = "%li";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_long_ints)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    long x1 = 0;
    long x2 = -12345;
    long x3 = 14;
    const char *format = "%li %li%li";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_min_long_int)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    long x = LONG_MIN;
    const char *format = "%li";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_long_int)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    long x = LONG_MAX;
    const char *format = "%li";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_dec)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    int x = 0;
    const char *format = "%d";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_decs)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    int x1 = 0;
    int x2 = -12345;
    int x3 = 14;
    const char *format = "%d %d%d";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_min_dec)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    int x = INT_MIN;
    const char *format = "%d";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_dec)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    int x = INT_MAX;
    const char *format = "%d";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_short_dec)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    short x = 0;
    const char *format = "%hd";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_short_decs)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    short x1 = 0;
    short x2 = -12345;
    short x3 = 14;
    const char *format = "%hd %hd%hd";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_min_short_dec)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    short x = SHRT_MIN;
    const char *format = "%hd";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_short_dec)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    short x = SHRT_MAX;
    const char *format = "%hd";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_long_dec)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    long x = 0;
    const char *format = "%ld";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_long_decs)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    long x1 = 0;
    long x2 = -12345;
    long x3 = 567678;
    const char *format = "%ld %ld%ld";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_min_long_dec)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    long x = LONG_MIN;
    const char *format = "%ld";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_long_dec)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    long x = LONG_MAX;
    const char *format = "%ld";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_octal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned int x = 0;
    const char *format = "%o";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_octals)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned int x1 = 0;
    unsigned int x2 = 12345;
    unsigned int x3 = 14;
    const char *format = "%o %o%o";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_octal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned int x = UINT_MAX;
    const char *format = "%o";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_short_octal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned short x = 0;
    const char *format = "%ho";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_short_octals)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned short x1 = 0;
    unsigned short x2 = 12345;
    unsigned short x3 = 14;
    const char *format = "%ho %ho%ho";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_short_octal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned short x = USHRT_MAX;
    const char *format = "%ho";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_long_octal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned long x = 0;
    const char *format = "%lo";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_long_octals)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned long x1 = 0;
    unsigned long x2 = 12345;
    unsigned long x3 = 18943;
    const char *format = "%lo %lo%lo";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_long_octal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned long x = ULONG_MAX;
    const char *format = "%lo";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_hexadecimal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned int x = 0;
    const char *format = "%x";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_hexadecimals)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned int x1 = 0;
    unsigned int x2 = 12345;
    unsigned int x3 = 14;
    const char *format = "%x %x%x";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_hexadecimal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned int x = UINT_MAX;
    const char *format = "%x";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_short_hexadecimal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned short x = 0;
    const char *format = "%hx";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_short_hexadecimals)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned short x1 = 0;
    unsigned short x2 = 12345;
    unsigned short x3 = 14;
    const char *format = "%hx %hx%hx";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_short_hexadecimal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned short x = USHRT_MAX;
    const char *format = "%hx";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_one_long_hexadecimal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned long x = 0;
    const char *format = "%lx";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_many_long_hexadecimals)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned long x1 = 0;
    unsigned long x2 = 12345;
    unsigned long x3 = 14;
    const char *format = "%lx %lx%lx";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x1, x2, x3), snprintf(s2, MYSTRING_LEN, format, x1, x2, x3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_max_long_hexadecimal)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    unsigned long x = ULONG_MAX;
    const char *format = "%lx";

    ck_assert_int_eq(my_snprintf(s1, MYSTRING_LEN, format, x), snprintf(s2, MYSTRING_LEN, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_format_len_equal_n)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    int x = 1;
    const char *format = "Dima%d";

    ck_assert_int_eq(my_snprintf(s1, 6, format, x), snprintf(s2, 6, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_little_n)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    int x = 1;
    const char *format = "Dima%d";

    ck_assert_int_eq(my_snprintf(s1, 5, format, x), snprintf(s2, 5, format, x));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_snprintf_zero_n)
{
    char s1[MYSTRING_LEN];
    char s2[MYSTRING_LEN];

    int x = 1;
    const char *format = "Dima%d";

    ck_assert_int_eq(my_snprintf(s1, 0, format, x), snprintf(s2, 0, format, x));
}
END_TEST

START_TEST(test_snprintf_null_str_zero_n)
{
    int x = 1;
    const char *format = "Dima%d";

    ck_assert_int_eq(my_snprintf(NULL, 0, format, x), snprintf(NULL, 0, format, x));
}
END_TEST

Suite *my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("My_snprintf tests");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_snprintf_one_char);
    tcase_add_test(tc_pos, test_snprintf_many_chars);
    tcase_add_test(tc_pos, test_snprintf_one_string);
    tcase_add_test(tc_pos, test_snprintf_many_strings);

    tcase_add_test(tc_pos, test_snprintf_one_int);
    tcase_add_test(tc_pos, test_snprintf_many_ints);
    tcase_add_test(tc_pos, test_snprintf_min_int);
    tcase_add_test(tc_pos, test_snprintf_max_int);
    tcase_add_test(tc_pos, test_snprintf_one_short_int);
    tcase_add_test(tc_pos, test_snprintf_many_short_ints);
    tcase_add_test(tc_pos, test_snprintf_min_short_int);
    tcase_add_test(tc_pos, test_snprintf_max_short_int);
    tcase_add_test(tc_pos, test_snprintf_one_long_int);
    tcase_add_test(tc_pos, test_snprintf_many_long_ints);
    tcase_add_test(tc_pos, test_snprintf_min_long_int);
    tcase_add_test(tc_pos, test_snprintf_max_long_int);

    tcase_add_test(tc_pos, test_snprintf_one_dec);
    tcase_add_test(tc_pos, test_snprintf_many_decs);
    tcase_add_test(tc_pos, test_snprintf_min_dec);
    tcase_add_test(tc_pos, test_snprintf_max_dec);
    tcase_add_test(tc_pos, test_snprintf_one_short_dec);
    tcase_add_test(tc_pos, test_snprintf_many_short_decs);
    tcase_add_test(tc_pos, test_snprintf_min_short_dec);
    tcase_add_test(tc_pos, test_snprintf_max_short_dec);
    tcase_add_test(tc_pos, test_snprintf_one_long_dec);
    tcase_add_test(tc_pos, test_snprintf_many_long_decs);
    tcase_add_test(tc_pos, test_snprintf_min_long_dec);
    tcase_add_test(tc_pos, test_snprintf_max_long_dec);

    tcase_add_test(tc_pos, test_snprintf_one_octal);
    tcase_add_test(tc_pos, test_snprintf_many_octals);
    tcase_add_test(tc_pos, test_snprintf_max_octal);
    tcase_add_test(tc_pos, test_snprintf_one_short_octal);
    tcase_add_test(tc_pos, test_snprintf_many_short_octals);
    tcase_add_test(tc_pos, test_snprintf_max_short_octal);
    tcase_add_test(tc_pos, test_snprintf_one_long_octal);
    tcase_add_test(tc_pos, test_snprintf_many_long_octals);
    tcase_add_test(tc_pos, test_snprintf_max_long_octal);

    tcase_add_test(tc_pos, test_snprintf_one_hexadecimal);
    tcase_add_test(tc_pos, test_snprintf_many_hexadecimals);
    tcase_add_test(tc_pos, test_snprintf_max_hexadecimal);
    tcase_add_test(tc_pos, test_snprintf_one_short_hexadecimal);
    tcase_add_test(tc_pos, test_snprintf_many_short_hexadecimals);
    tcase_add_test(tc_pos, test_snprintf_max_short_hexadecimal);
    tcase_add_test(tc_pos, test_snprintf_one_long_hexadecimal);
    tcase_add_test(tc_pos, test_snprintf_many_long_hexadecimals);
    tcase_add_test(tc_pos, test_snprintf_max_long_hexadecimal);

    tcase_add_test(tc_pos, test_snprintf_format_len_equal_n);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_snprintf_little_n);
    tcase_add_test(tc_neg, test_snprintf_zero_n);
    tcase_add_test(tc_neg, test_snprintf_null_str_zero_n);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
