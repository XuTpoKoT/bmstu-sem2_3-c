#define _GNU_SOURCE

#include "check_films.h"

START_TEST(test_insert_sorted_beg)
{
    films_t films, films_res;
    size_t nmemb = 3;
    films_malloc(&films, nmemb + 1);
    films.data[0].title = strdup("title1");
    films.data[0].name = strdup("name1");
    films.data[0].year = 2001;

    films.data[1].title = strdup("title2");
    films.data[1].name = strdup("name2");
    films.data[1].year = 2002;

    films.data[2].title = strdup("title3");
    films.data[2].name = strdup("name3");
    films.data[2].year = 2003;
    films.nmemb = nmemb;

    films_malloc(&films_res, nmemb + 1);

    films_res.data[0].title = strdup("title");
    films_res.data[0].name = strdup("name");
    films_res.data[0].year = 2000;

    films_res.data[1].title = strdup("title1");
    films_res.data[1].name = strdup("name1");
    films_res.data[1].year = 2001;

    films_res.data[2].title = strdup("title2");
    films_res.data[2].name = strdup("name2");
    films_res.data[2].year = 2002;

    films_res.data[3].title = strdup("title3");
    films_res.data[3].name = strdup("name3");
    films_res.data[3].year = 2003;
    films_res.nmemb = nmemb + 1;

    film_t film = { .title = "title", .name = "name", .year = 2000 };

    ck_assert_int_eq(films_insert_sorted(&film, &films, "year"), EXIT_SUCCESS);
    ck_assert_int_eq(films_equal(&films, &films_res), true);
    films_free(&films);
    films_free(&films_res);
}
END_TEST

START_TEST(test_insert_sorted_title)
{
    films_t films, films_res;
    size_t nmemb = 3;
    films_malloc(&films, nmemb + 1);
    films.data[0].title = strdup("title1");
    films.data[0].name = strdup("name1");
    films.data[0].year = 2001;

    films.data[1].title = strdup("title2");
    films.data[1].name = strdup("name2");
    films.data[1].year = 2002;

    films.data[2].title = strdup("title4");
    films.data[2].name = strdup("name4");
    films.data[2].year = 2004;
    films.nmemb = nmemb;

    films_malloc(&films_res, nmemb + 1);

    films_res.data[0].title = strdup("title1");
    films_res.data[0].name = strdup("name1");
    films_res.data[0].year = 2001;

    films_res.data[1].title = strdup("title2");
    films_res.data[1].name = strdup("name2");
    films_res.data[1].year = 2002;

    films_res.data[2].title = strdup("title3");
    films_res.data[2].name = strdup("name3");
    films_res.data[2].year = 2003;

    films_res.data[3].title = strdup("title4");
    films_res.data[3].name = strdup("name4");
    films_res.data[3].year = 2004;
    films_res.nmemb = nmemb + 1;

    film_t film = { .title = "title3", .name = "name3", .year = 2003 };

    ck_assert_int_eq(films_insert_sorted(&film, &films, "title"), EXIT_SUCCESS);
    ck_assert_int_eq(films_equal(&films, &films_res), true);
    films_free(&films);
    films_free(&films_res);
}
END_TEST

START_TEST(test_insert_sorted_name)
{
    films_t films, films_res;
    size_t nmemb = 3;
    films_malloc(&films, nmemb + 1);
    films.data[0].title = strdup("title1");
    films.data[0].name = strdup("name1");
    films.data[0].year = 2001;

    films.data[1].title = strdup("title2");
    films.data[1].name = strdup("name2");
    films.data[1].year = 2002;

    films.data[2].title = strdup("title4");
    films.data[2].name = strdup("name4");
    films.data[2].year = 2004;
    films.nmemb = nmemb;

    films_malloc(&films_res, nmemb + 1);

    films_res.data[0].title = strdup("title1");
    films_res.data[0].name = strdup("name1");
    films_res.data[0].year = 2001;

    films_res.data[1].title = strdup("title2");
    films_res.data[1].name = strdup("name2");
    films_res.data[1].year = 2002;

    films_res.data[2].title = strdup("title3");
    films_res.data[2].name = strdup("name3");
    films_res.data[2].year = 2003;

    films_res.data[3].title = strdup("title4");
    films_res.data[3].name = strdup("name4");
    films_res.data[3].year = 2004;
    films_res.nmemb = nmemb + 1;

    film_t film = { .title = "title3", .name = "name3", .year = 2003 };

    ck_assert_int_eq(films_insert_sorted(&film, &films, "name"), EXIT_SUCCESS);
    ck_assert_int_eq(films_equal(&films, &films_res), true);
    films_free(&films);
    films_free(&films_res);
}
END_TEST

START_TEST(test_insert_sorted_year)
{
    films_t films, films_res;
    size_t nmemb = 3;
    films_malloc(&films, nmemb + 1);
    films.data[0].title = strdup("title1");
    films.data[0].name = strdup("name1");
    films.data[0].year = 2001;

    films.data[1].title = strdup("title2");
    films.data[1].name = strdup("name2");
    films.data[1].year = 2002;

    films.data[2].title = strdup("title4");
    films.data[2].name = strdup("name4");
    films.data[2].year = 2004;
    films.nmemb = nmemb;

    films_malloc(&films_res, nmemb + 1);

    films_res.data[0].title = strdup("title1");
    films_res.data[0].name = strdup("name1");
    films_res.data[0].year = 2001;

    films_res.data[1].title = strdup("title2");
    films_res.data[1].name = strdup("name2");
    films_res.data[1].year = 2002;

    films_res.data[2].title = strdup("title3");
    films_res.data[2].name = strdup("name3");
    films_res.data[2].year = 2003;

    films_res.data[3].title = strdup("title4");
    films_res.data[3].name = strdup("name4");
    films_res.data[3].year = 2004;
    films_res.nmemb = nmemb + 1;

    film_t film = { .title = "title3", .name = "name3", .year = 2003 };

    ck_assert_int_eq(films_insert_sorted(&film, &films, "year"), EXIT_SUCCESS);
    ck_assert_int_eq(films_equal(&films, &films_res), true);
    films_free(&films);
    films_free(&films_res);
}
END_TEST

Suite* insert_sorted_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("insert_sorted");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_insert_sorted_beg);
    tcase_add_test(tc_pos, test_insert_sorted_title);
    tcase_add_test(tc_pos, test_insert_sorted_name);
    tcase_add_test(tc_pos, test_insert_sorted_year);

    suite_add_tcase(s, tc_pos);

    return s;
} 