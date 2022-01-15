#include "check_list.h"

int cmp_int(const void *a, const void *b)
{
    const int *x = a;
    const int *y = b;
    return *x - *y;
}

START_TEST(test_find_mid)
{
    int arr[] = { 1, 3, 2, 4, 5 };
    node_t *head = list_create_node(&arr[0]);
    for (size_t i = 1; i < 5; i++)
    {
        node_t *node = list_create_node(&arr[i]);
        list_push(&head, node);
    }

    node_t *node = find(head, &arr[2], cmp_int);
    ck_assert_ptr_eq(node->data, &arr[2]);
    list_free_all(&head);
}
END_TEST

START_TEST(test_find_beg)
{
    int arr[] = { 1, 3, 2, 4, 5 };
    node_t *head = list_create_node(&arr[0]);
    for (size_t i = 1; i < 5; i++)
    {
        node_t *node = list_create_node(&arr[i]);
        list_push(&head, node);
    }

    node_t *node = find(head, &arr[0], cmp_int);
    ck_assert_ptr_eq(node->data, &arr[0]);
    list_free_all(&head);
}
END_TEST

START_TEST(test_find_end)
{
    int arr[] = { 1, 3, 2, 4, 5 };
    node_t *head = list_create_node(&arr[0]);
    for (size_t i = 1; i < 5; i++)
    {
        node_t *node = list_create_node(&arr[i]);
        list_push(&head, node);
    }

    node_t *node = find(head, &arr[4], cmp_int);
    ck_assert_ptr_eq(node->data, &arr[4]);
    list_free_all(&head);
}
END_TEST

Suite* find_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("find");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_find_mid);
    tcase_add_test(tc_pos, test_find_beg);
    tcase_add_test(tc_pos, test_find_end);

    suite_add_tcase(s, tc_pos);

    return s;
} 


START_TEST(test_reverse_one)
{
    int arr[] = { 1 };
    node_t *head = list_create_node(&arr[0]);

    reverse(head);
    ck_assert_ptr_eq(head->data, &arr[0]);    
    list_free_all(&head);
}
END_TEST

START_TEST(test_reverse_two)
{
    int arr[] = { 1, 2 };
    node_t *head = list_create_node(&arr[0]);
    for (size_t i = 1; i < 2; i++)
    {
        node_t *node = list_create_node(&arr[i]);
        list_push(&head, node);
    }

    reverse(head);
    node_t *node = head;
    for (size_t i = 0; i < 2; i++)
    {
        ck_assert_ptr_eq(node->data, &arr[i]);
        node = node->next;
    }       
    list_free_all(&head);
}
END_TEST

START_TEST(test_reverse_usual)
{
    int arr[] = { 1, 3, 2, 4, 5 };
    node_t *head = list_create_node(&arr[0]);
    for (size_t i = 1; i < 5; i++)
    {
        node_t *node = list_create_node(&arr[i]);
        list_push(&head, node);
    }

    reverse(head);
    node_t *node = head;
    for (size_t i = 0; i < 5; i++)
    {
        ck_assert_ptr_eq(node->data, &arr[i]);
        node = node->next;
    }       
    list_free_all(&head);
}
END_TEST

Suite* reverse_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("reverse");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_reverse_one);
    tcase_add_test(tc_pos, test_reverse_two);
    tcase_add_test(tc_pos, test_reverse_usual);

    suite_add_tcase(s, tc_pos);

    return s;
} 

START_TEST(test_sorted_insert_mid)
{
    int arr[] = { 5, 4, 3, 2, 1 };
    size_t nmemb = sizeof(arr) / sizeof(arr[0]);
    node_t *head = list_create_node(&arr[0]);
    for (size_t i = 1; i < nmemb; i++)
        if (i != 2)
        {
            node_t *node = list_create_node(&arr[i]);
            list_push(&head, node);
        }

    node_t *elem = list_create_node(&arr[2]);
    sorted_insert(&head, elem, cmp_int);
    node_t *node = head;
    for (size_t i = 0; i < nmemb; i++)
    {
        ck_assert_int_eq(*(int*)node->data, arr[nmemb - 1 - i]);
        node = node->next;
    }       
    list_free_all(&head);
}
END_TEST

START_TEST(test_sorted_insert_beg)
{
    int arr[] = { 5, 4, 3, 2, 1 };
    size_t nmemb = sizeof(arr) / sizeof(arr[0]);
    node_t *head = list_create_node(&arr[0]);
    for (size_t i = 1; i < nmemb - 1; i++)
    {
        node_t *node = list_create_node(&arr[i]);
        list_push(&head, node);
    }

    node_t *elem = list_create_node(&arr[4]);
    sorted_insert(&head, elem, cmp_int);
    node_t *node = head;
    for (size_t i = 0; i < nmemb; i++)
    {
        ck_assert_int_eq(*(int*)node->data, arr[nmemb - 1 - i]);
        node = node->next;
    }       
    list_free_all(&head);
}
END_TEST

START_TEST(test_sorted_insert_end)
{
    int arr[] = { 5, 4, 3, 2, 1 };
    size_t nmemb = sizeof(arr) / sizeof(arr[0]);
    node_t *head = list_create_node(&arr[1]);
    for (size_t i = 2; i < nmemb; i++)
    {
        node_t *node = list_create_node(&arr[i]);
        list_push(&head, node);
    }       

    node_t *elem = list_create_node(&arr[0]);
    sorted_insert(&head, elem, cmp_int);
    node_t *node = head;
    for (size_t i = 0; i < nmemb; i++)
    {
        ck_assert_int_eq(*(int*)node->data, arr[nmemb - 1 - i]);
        node = node->next;
    }       
    list_free_all(&head);
}
END_TEST

Suite* sorted_insert_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sorted_insert");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sorted_insert_mid);
    tcase_add_test(tc_pos, test_sorted_insert_beg);
    tcase_add_test(tc_pos, test_sorted_insert_end);

    suite_add_tcase(s, tc_pos);

    return s;
} 

START_TEST(test_sort_random)
{
    int arr_s[] = { 5, 4, 3, 2, 1 };
    size_t nmemb = sizeof(arr_s) / sizeof(arr_s[0]);
    node_t *head_s = list_create_node(&arr_s[0]);
    for (size_t i = 1; i < nmemb; i++)
    {
        node_t *node = list_create_node(&arr_s[i]);
        list_push(&head_s, node);
    }

    int arr[] = { 2, 3, 1, 5, 4 };
    node_t *head = list_create_node(&arr[0]);
    for (size_t i = 1; i < nmemb; i++)
    {
        node_t *node = list_create_node(&arr[i]);
        list_push(&head, node);
    }

    node_t *new_head = sort(head, cmp_int);
    node_t *node = new_head;
    node_t *node_s = head_s;
    for (size_t i = 0; i < nmemb; i++)
    {
        ck_assert_int_eq(*(int*)node->data, *(int*)node_s->data);
        node = node->next;
        node_s = node_s->next;
    }       
    list_free_all(&head);
    list_free_all(&head_s);
    list_free_all(&new_head);
}
END_TEST



START_TEST(test_sort_sorted)
{
    int arr_s[] = { 5, 4, 3, 2, 1 };
    size_t nmemb = sizeof(arr_s) / sizeof(arr_s[0]);
    node_t *head_s = list_create_node(&arr_s[0]);
    for (size_t i = 1; i < nmemb; i++)
    {
        node_t *node = list_create_node(&arr_s[i]);
        list_push(&head_s, node);
    }

    int arr[] = { 5, 4, 3, 2, 1 };
    node_t *head = list_create_node(&arr[0]);
    for (size_t i = 1; i < nmemb; i++)
    {
        node_t *node = list_create_node(&arr[i]);
        list_push(&head, node);
    }

    node_t *new_head = sort(head, cmp_int);
    node_t *node = new_head;
    node_t *node_s = head_s;
    for (size_t i = 0; i < nmemb; i++)
    {
        ck_assert_int_eq(*(int*)node->data, *(int*)node_s->data);
        node = node->next;
        node_s = node_s->next;
    }       
    list_free_all(&head);
    list_free_all(&head_s);
    list_free_all(&new_head);
}
END_TEST

START_TEST(test_sort_unsorted)
{
    int arr_s[] = { 5, 4, 3, 2, 1 };
    size_t nmemb = sizeof(arr_s) / sizeof(arr_s[0]);
    node_t *head_s = list_create_node(&arr_s[0]);
    for (size_t i = 1; i < nmemb; i++)
    {
        node_t *node = list_create_node(&arr_s[i]);
        list_push(&head_s, node);
    }

    int arr[] = { 1, 2, 3, 4, 5 };
    node_t *head = list_create_node(&arr[0]);
    for (size_t i = 1; i < nmemb; i++)
    {
        node_t *node = list_create_node(&arr[i]);
        list_push(&head, node);
    }

    node_t *new_head = sort(head, cmp_int);
    node_t *node = new_head;
    node_t *node_s = head_s;
    for (size_t i = 0; i < nmemb; i++)
    {
        ck_assert_int_eq(*(int*)node->data, *(int*)node_s->data);
        node = node->next;
        node_s = node_s->next;
    }       
    list_free_all(&head);
    list_free_all(&head_s);
    list_free_all(&new_head);
}
END_TEST

START_TEST(test_sort_one_elem)
{
    int arr_s[] = { 5 };
    size_t nmemb = sizeof(arr_s) / sizeof(arr_s[0]);
    node_t *head_s = list_create_node(&arr_s[0]);

    int arr[] = { 5 };
    node_t *head = list_create_node(&arr[0]);

    node_t *new_head = sort(head, cmp_int);
    node_t *node = new_head;
    node_t *node_s = head_s;
    for (size_t i = 0; i < nmemb; i++)
    {
        ck_assert_int_eq(*(int*)node->data, *(int*)node_s->data);
        node = node->next;
        node_s = node_s->next;
    }       
    list_free_all(&head);
    list_free_all(&head_s);
    list_free_all(&new_head);
}
END_TEST

START_TEST(test_sort_same)
{
    int arr_s[] = { 3, 3, 2, 1, 1 };
    size_t nmemb = sizeof(arr_s) / sizeof(arr_s[0]);
    node_t *head_s = list_create_node(&arr_s[0]);
    for (size_t i = 1; i < nmemb; i++)
    {
        node_t *node = list_create_node(&arr_s[i]);
        list_push(&head_s, node);
    }

    int arr[] = { 3, 2, 1, 1, 3 };
    node_t *head = list_create_node(&arr[0]);
    for (size_t i = 1; i < nmemb; i++)
    {
        node_t *node = list_create_node(&arr[i]);
        list_push(&head, node);
    }

    node_t *new_head = sort(head, cmp_int);
    node_t *node = new_head;
    node_t *node_s = head_s;
    for (size_t i = 0; i < nmemb; i++)
    {
        ck_assert_int_eq(*(int*)node->data, *(int*)node_s->data);
        node = node->next;
        node_s = node_s->next;
    }       
    list_free_all(&head);
    list_free_all(&head_s);
    list_free_all(&new_head);
}
END_TEST

Suite* sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sort");      
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sort_random);
    tcase_add_test(tc_pos, test_sort_sorted);
    tcase_add_test(tc_pos, test_sort_unsorted);
    tcase_add_test(tc_pos, test_sort_one_elem);
    tcase_add_test(tc_pos, test_sort_same);

    suite_add_tcase(s, tc_pos);

    return s;
} 
