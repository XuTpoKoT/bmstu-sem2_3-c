#include "students.h"

#include <string.h>
#include <stdlib.h>

int file_size(FILE *f, long *count_students)
{
    long pos = ftell(f);
    if (pos < 0)
        return EXIT_FAILURE;
    if (fseek(f, 0L, SEEK_END))
        return EXIT_FAILURE;
    long size = ftell(f);
    if (size < 0)
        return EXIT_FAILURE;

    *count_students = size / sizeof(student_t);
    if (*count_students * sizeof(student_t) != (size_t)size)
        return EXIT_FAILURE;

    return fseek(f, pos, SEEK_SET);
}

int get_student_by_pos(FILE *f, long pos, student_t *student)
{
    long cur_pos = ftell(f);
    if (cur_pos < 0)
        return EXIT_FAILURE;
    if (fseek(f, pos * sizeof(student_t), SEEK_SET))
        return EXIT_FAILURE;
    if (fread(student, sizeof(student_t), 1, f) != 1)
        return EXIT_FAILURE;
    return fseek(f, cur_pos, SEEK_SET);
}

int put_student_by_pos(FILE *f, long pos, const student_t *student)
{
    long cur_pos = ftell(f);
    if (cur_pos < 0)
        return EXIT_FAILURE;
    if (fseek(f, pos * sizeof(student_t), SEEK_SET))
        return EXIT_FAILURE;
    if (fwrite(student, sizeof(student_t), 1, f) != 1)
        return EXIT_FAILURE;
    return fseek(f, cur_pos, SEEK_SET);
}

int del_students_between(FILE *f, const char beg[], const char end[])
{
    long count_students;
    student_t del_student = { .fam = "0000", .num = 0};
    if (file_size(f, &count_students))
        return EXIT_FAILURE;

    long i;
    for (i= 0; i < count_students; i++)
    {
        student_t student1, student2;
        if (get_student_by_pos(f, i, &student1))
            return EXIT_FAILURE;
        if (strcmp(student1.fam, beg) >= 0 && strcmp(student1.fam, end) <= 0)
        {
            for (long j = i; j < count_students - 1; j++)
            {
                if (get_student_by_pos(f, j + 1, &student2))
                    return EXIT_FAILURE;
                if (put_student_by_pos(f, j, &student2))
                    return EXIT_FAILURE;
            }
            i--;
            count_students--;
        }
    }

    return put_student_by_pos(f, i, &del_student);
}
