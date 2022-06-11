#include <stdio.h>
#include <string.h>
#include "student.h"

void print_student(student_t student)
{
    printf("%s\n%s\n", student.surname, student.name);
    for (int i = 0; i < SUBJECTS_AMOUNT; i++)
        printf("%u\n", student.grades[i]);
}

// 1 если объект big "больше" объекта small, иначе 0 
int compare(student_t small, student_t big)
{
    int result = strcmp(big.surname, small.surname);
    if (result == 0)
        result = strcmp(big.name, small.name);

    return result > 0;
}

double average_grade(student_t student)
{
    double average = 0;

    if (SUBJECTS_AMOUNT != 0)
    {
        for (int i = 0; i < SUBJECTS_AMOUNT; i++)
            average += student.grades[i];
        
        average /= SUBJECTS_AMOUNT;
    }

    return average;
}