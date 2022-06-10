#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <inttypes.h>

#define OK          0
#define ERR_IO      1
#define ERR_DATA    2
#define ERR_ARGS    53
#define ERR_NO_FILE 4

#define NAME_LENGTH     25
#define SURNAME_LENGTH  10
#define SUBJECTS_AMOUNT 4

typedef struct 
{
    char name[NAME_LENGTH + 1];
    char surname[SURNAME_LENGTH + 1];
    uint32_t grades[SUBJECTS_AMOUNT];
} student_t;

int print_students(FILE *f);

int sort_file(FILE *f);

int compare(student_t small, student_t big);

void print_student(student_t student);

student_t get_student_by_pos(FILE *f, int pos);

int put_student_by_pos(FILE *f, int pos, student_t student);

int delete_student_by_pos(FILE *f, int pos);

double average_grade(student_t student);

double count_average_grade(FILE *f);

int print_appropriate_students(FILE *src, FILE *dst, const char *sub_surname);

int delete_students(FILE *f);

long size_of_file(FILE *f);

int is_typed_file(FILE *f);

#endif