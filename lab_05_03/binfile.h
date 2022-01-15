#ifndef _BINFILE_H_
#define _BINFILE_H_

#include <stdio.h>
#include <stdlib.h>

#define WRONG_ARGS 1
#define WRONG_NUMBER 2
#define FILL_ERROR 3
#define NO_FILE 4
#define PRINT_ERROR 5
#define SORT_ERROR 6
#define TXT_TO_BIN_ERROR 7
#define BIN_TO_TXT_ERROR 8

int file_size(FILE *f, size_t *count_numbers);
int get_number_by_pos(FILE *f, long pos, int *num);
int put_number_by_pos(FILE *f, long pos, int *num);
int rand_int(const int min, const int max);
int fill_with_int(FILE *f, size_t numbers);
int print(FILE *f);
int bubble_sort(FILE *f);
int txt_to_bin(FILE *fsrc, FILE *fdst);
int bin_to_txt(FILE *fsrc, FILE *fdst);

#endif
