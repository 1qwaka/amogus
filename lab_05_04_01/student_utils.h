#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <inttypes.h>
#include "student.h"

#define OK              0
#define ERR_IO          1
#define ERR_DATA        2
#define ERR_ARGS        53
#define ERR_NO_FILE     4
#define ERR_GET_STUDENT 5
#define ERR_PUT_STUDENT 6
#define ERR_TRUNCATE    7

int print_students(FILE *f);

int sort_file(FILE *f);

int get_student_by_pos(FILE *f, int pos, student_t *student);

int put_student_by_pos(FILE *f, int pos, student_t student);

int delete_student_by_pos(FILE *f, int pos);

int count_average_grade(FILE *f, double *result);

int print_appropriate_students(FILE *src, FILE *dst, const char *sub_surname);

int delete_students(FILE *f);

long size_of_file(FILE *f);

int is_typed_file(FILE *f);

#endif  // _UTILS_H_