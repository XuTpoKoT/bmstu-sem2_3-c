#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matr.h"
#include "sparse_matr.h"
#include "mystring.h"
#include "cmp.h"

typedef enum
{
    out,
    sum,
    mul,
    del_row,
    wrong_action
} action_t;

action_t define_action(const char *str)
{
    if (!strcmp(str, "out"))
        return out;
    if (!strcmp(str, "add"))
        return sum;
    if (!strcmp(str, "mul"))
        return mul;
    if (!strcmp(str, "lin"))
        return del_row;
    return wrong_action;
}

int main(void)
{
    setbuf(stdout, NULL);
    char action_str[MYSTRING_LEN];
    action_t action;
    size_t rows, cols;
    matr_t matr1, matr2;
    sparse_matr_t *sparse_matr1, *sparse_matr2;
    
    if (fscan_str(action_str, MYSTRING_LEN, stdin))
        return EXIT_FAILURE;
    
    if ((action = define_action(action_str)) == wrong_action)
        return EXIT_FAILURE;
    
    if (scanf("%zu%zu", &rows, &cols) != 2)
        return EXIT_FAILURE;

    if (matr_malloc(rows, cols, &matr1))
        return EXIT_FAILURE;

    if (matr_scan(&matr1))
    {
        matr_free(&matr1);
        return EXIT_FAILURE;
    }

    if (!(sparse_matr1 = matr_to_sparse_matr(&matr1)))
    {
        matr_free(&matr1);
        return EXIT_FAILURE;
    }
    matr_free(&matr1); 

    switch (action)
    {
        case out:
            sparse_matr_fprint(stdout, sparse_matr1, INT_FORMAT);
            break;
        case del_row:
            {
                size_t row = sparse_matr_find_row_with_max(sparse_matr1);
                sparse_matr_del_row(&sparse_matr1, row);
                if (!sparse_matr1)
                    return EXIT_FAILURE;
                sparse_matr_fprint(stdout, sparse_matr1, INT_FORMAT);
            }
            break;
        case sum:
        case mul:
            {
                // чтение 2-й матрицы
                if (scanf("%zu%zu", &rows, &cols) != 2)
                {
                    sparse_matr_free(&sparse_matr1);
                    return EXIT_FAILURE;
                }
                    

                if (matr_malloc(rows, cols, &matr2))
                {
                    sparse_matr_free(&sparse_matr1);
                    return EXIT_FAILURE;
                }
                    
                if (matr_scan(&matr2))
                {
                    sparse_matr_free(&sparse_matr1);
                    matr_free(&matr2);
                    return EXIT_FAILURE;
                }

                if (!(sparse_matr2 = matr_to_sparse_matr(&matr2)))
                {
                    sparse_matr_free(&sparse_matr1);
                    matr_free(&matr2);
                    return EXIT_FAILURE;
                }
                matr_free(&matr2);

                //sparse_matr_fprint(stdout, sparse_matr1, INT_FORMAT); // debug
                //sparse_matr_fprint(stdout, sparse_matr2, INT_FORMAT);

                switch (action)
                {
                    case sum:
                        {
                            sparse_matr_t *res = sparse_matr_sum(sparse_matr1, sparse_matr2);
                            if (!res)
                            {
                                sparse_matr_free(&sparse_matr2);
                                sparse_matr_free(&sparse_matr1);
                                return EXIT_FAILURE;
                            }
                            sparse_matr_fprint(stdout, res, INT_FORMAT);
                            sparse_matr_free(&res);
                            break;
                        }                        
                    case mul:
                        {
                            sparse_matr_t *res = sparse_matr_mul(sparse_matr1, sparse_matr2);
                            if (!res)
                            {
                                sparse_matr_free(&sparse_matr2);
                                sparse_matr_free(&sparse_matr1);
                                return EXIT_FAILURE;
                            }
                            sparse_matr_fprint(stdout, res, INT_FORMAT);
                            sparse_matr_free(&res);                
                            break;
                        }                        
                    default:
                        break;
                }

                sparse_matr_free(&sparse_matr2);
                break;
            }
        default:
            break;
    }

    sparse_matr_free(&sparse_matr1);
    //printf("\nEnd\n");
                  
    return EXIT_SUCCESS;
}

