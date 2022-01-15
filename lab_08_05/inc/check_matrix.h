#ifndef CHECK_MATRIX_H
#define CHECK_MATRIX_H

#include "matrix.h"
#include <check.h>

Suite* trunc_to_square_suite(void);
Suite* make_sym_size_suite(void);
Suite* mul_suite(void);
Suite* pow_suite(void);

#endif