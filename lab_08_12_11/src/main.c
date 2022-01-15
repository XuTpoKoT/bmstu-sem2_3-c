#include "matrix.h"

#include <string.h>

#define MIN_ARGS 4
#define MAX_ARGS 5

#define FILENAME_LEN 25

typedef enum
{
    sum,
    mul,
    det
} action_t;

int define_action(char *action_str, action_t *action)
{
    if (!strcmp(action_str, "a"))
    {
        *action = sum;
        return EXIT_SUCCESS;
    }
    if (!strcmp(action_str, "m"))
    {
        *action = mul;
        return EXIT_SUCCESS;
    }
    if (!strcmp(action_str, "o"))
    {
        *action = det;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int parse_args(int argc, char **argv, action_t *action, char *fsrc1_name, char *fsrc2_name, char *fdst_name)
{
    if (argc > MAX_ARGS || argc < MIN_ARGS)
        return ERR_WRONG_ARG_COUNT;

    if (define_action(argv[1], action))
        return ERR_WRONG_KEY;

    if (*action == det && argc == 5)
        return ERR_WRONG_ARG_COUNT;

    strcpy(fsrc1_name, argv[2]);

    if (argc == 5)
    {
        strcpy(fsrc2_name, argv[3]);
        strcpy(fdst_name, argv[4]);
    }
    else
    {
        fsrc2_name = NULL;
        strcpy(fdst_name, argv[3]);
    }
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    action_t action;
    char fsrc1_name[FILENAME_LEN], fsrc2_name[FILENAME_LEN], fdst_name[FILENAME_LEN]; 
    FILE *fsrc1 = NULL, *fsrc2 = NULL, *fdst = NULL;
    long long buf_rows, buf_cols;
    size_t n, m;
    matrix_t a;
    size_t p, q;
    matrix_t b;
    int rc;
    
    if ((rc = parse_args(argc, argv, &action, fsrc1_name, fsrc2_name, fdst_name)))
        return rc;
    
    // чтение 1-й матрицы
    fsrc1 = fopen(fsrc1_name, "r");
    if (fsrc1 == NULL)
        return ERR_OPEN_FILE;

    if (fscanf(fsrc1, "%lld%lld", &buf_rows, &buf_cols) != 2 || buf_rows <= 0 || buf_cols <= 0)
    {
        fclose(fsrc1);
        return ERR_READ;
    }
        
    n = buf_rows;
    m = buf_cols;

    if (matrix_create(n, m, &a))
    {
        fclose(fsrc1);
        return ERR_MALLOC;
    }
        
    if (matrix_fread(fsrc1, &a))
    {
        matrix_free(&a);
        fclose(fsrc1);
        return ERR_READ;
    }

    // открытие выходного файла
    fdst = fopen(fdst_name, "w");
    if (fdst == NULL)
    {
        matrix_free(&a);
        fclose(fsrc1);
        return ERR_OPEN_FILE;
    }
        
    switch (action)
    {
        case sum:
            {
                // чтение 2-й матрицы
                fsrc2 = fopen(fsrc2_name, "r");
                if (fsrc2 == NULL)
                {
                    rc = ERR_OPEN_FILE;
                    goto free_src1;
                }
              
                if (fscanf(fsrc2, "%lld%lld", &buf_rows, &buf_cols) != 2 || buf_rows <= 0 || buf_cols <= 0)
                {
                    rc = ERR_READ;
                    goto free_src1;
                }
                p = buf_rows;
                q = buf_cols;

                if (matrix_create(p, q, &b))
                {
                    rc = ERR_MALLOC;
                    goto free_src1;
                }

                if (matrix_fread(fsrc2, &b))
                {
                    rc = ERR_READ;
                    goto free_all_srcs;
                }

                // сложение матриц
                matrix_t sum_matr;
                if (matrix_create(a.rows, a.cols, &sum_matr))
                {
                    rc = ERR_MALLOC;
                    goto free_all_srcs;
                }
                if (matrix_sum(&a, &b, &sum_matr))
                {
                    matrix_free(&sum_matr);
                    rc = ERR_SUM;
                    goto free_all_srcs;
                }
                // запись результата
                matrix_fwrite(fdst, &sum_matr);
                matrix_free(&sum_matr);
                break;
            }
        case mul:
            {
                // чтение 2-й матрицы
                fsrc2 = fopen(fsrc2_name, "r");
                if (fsrc2 == NULL)
                {
                    rc = ERR_OPEN_FILE;
                    goto free_src1;
                }
               
                if (fscanf(fsrc2, "%lld%lld", &buf_rows, &buf_cols) != 2 || buf_rows <= 0 || buf_cols <= 0)
                {
                    rc = ERR_READ;
                    goto free_src1;
                }
                p = buf_rows;
                q = buf_cols;

                if (matrix_create(p, q, &b))
                {
                    rc = ERR_MALLOC;
                    goto free_src1;
                }

                if (matrix_fread(fsrc2, &b))
                {
                    rc = ERR_READ;
                    goto free_all_srcs;
                }

                // умножение матриц
                matrix_t mul_matr;
                if (matrix_create(a.rows, b.cols, &mul_matr))
                {
                    rc = ERR_MALLOC;
                    goto free_all_srcs;
                }
                if (matrix_mul(&a, &b, &mul_matr))
                {
                    matrix_free(&mul_matr);
                    rc = ERR_MUL;
                    goto free_all_srcs;
                }
                // запись результата
                matrix_fwrite(fdst, &mul_matr);
                matrix_free(&mul_matr);
                break;
            }
        case det:
            {
                // вычисление определителя
                double det_matr;

                if (matrix_det(&a, &det_matr))
                {
                    rc = ERR_DET;
                    goto free_all_srcs;
                }
                // запись результата
                fprintf(fdst, "%.6lf\n", det_matr);
                break;
            }
        default:
            break;
    } // switch action

    free_all_srcs:
    if (argc == 5)
        matrix_free(&b);

    free_src1:
        fclose(fsrc1);
    if (fsrc2)
        fclose(fsrc2);
    fclose(fdst);
    matrix_free(&a);

    return rc;
}
