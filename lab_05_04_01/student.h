#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <inttypes.h>

#define NAME_LENGTH     10
#define SURNAME_LENGTH  25
#define SUBJECTS_AMOUNT 4

typedef struct 
{
    char surname[SURNAME_LENGTH + 1];
    char name[NAME_LENGTH + 1];
    uint32_t grades[SUBJECTS_AMOUNT];
} student_t;

void print_student(student_t student);

double average_grade(student_t student);

int compare(student_t small, student_t big);

#endif  // _STUDENT_H_