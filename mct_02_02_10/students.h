#ifndef _STUDENTS_H_
#define _STUDENTS_H_

#include <stdio.h>
#include <inttypes.h>

#define MAX_FAM_LEN 126

#pragma pack(push, 1)
typedef struct
{
    char fam[MAX_FAM_LEN];
    int64_t num;
} student_t;
#pragma pack(pop)

int file_size(FILE *f, long *count_students);
int get_student_by_pos(FILE *f, long pos, student_t *student);
int put_student_by_pos(FILE *f, long pos, const student_t *student);
int del_students_between(FILE *f, const char beg[], const char end[]);

#endif
