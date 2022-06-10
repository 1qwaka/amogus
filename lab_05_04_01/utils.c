#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"


int print_students(FILE *f)
{
    int rc = OK;
    student_t tmp = { 0 };
    
    if (is_typed_file(f))
    {
        fseek(f, 0, SEEK_SET);
        while (fread(&tmp, sizeof(tmp), 1, f) == 1)
            print_student(tmp);
    
        if (ferror(f))
            rc = ERR_IO;
    }
    else
    {
        rc = ERR_DATA;
    }
    
    return rc;
}

void print_student(student_t student)
{
    printf("%s\n%s\n", student.name, student.surname);
    for (int i = 0; i < SUBJECTS_AMOUNT; i++)
        printf("%u ", student.grades[i]);
    printf("\n");    
}

int sort_file(FILE *f)
{
    int rc = OK;

    if (is_typed_file(f))
    {
        long size = size_of_file(f) / sizeof(student_t);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size - i - 1; j++)
            {
                student_t cur = get_student_by_pos(f, j);
                student_t next = get_student_by_pos(f, j + 1);
                if (compare(next, cur))
                {
                    put_student_by_pos(f, j, next);
                    put_student_by_pos(f, j + 1, cur);
                }
            }    
    }
    else
    {
        rc = ERR_DATA;
    }
   
    return rc;
}

// 1 если объект big "больше" объекта small, иначе 0 
int compare(student_t small, student_t big)
{
    int result = strcmp(big.name, small.name) > 0;
    if (result == 0)
        result = strcmp(big.surname, small.surname) > 0;

    return result;
}

student_t get_student_by_pos(FILE *f, int pos)
{
    student_t result = { 0 };
    fseek(f, sizeof(result) * pos, SEEK_SET);
    fread(&result, sizeof(result), 1, f);
    return result;
}

int put_student_by_pos(FILE *f, int pos, student_t student)
{
    fseek(f, sizeof(student) * pos, SEEK_SET);
    int rc = fwrite(&student, sizeof(student), 1, f) == 1 ? OK : ERR_IO;
    return rc;
}

int print_appropriate_students(FILE *src, FILE *dst, const char *sub_surname)
{
    int rc = OK;

    if (is_typed_file(src))
    {
        int pos = 0;
        int size = size_of_file(src) / sizeof(student_t);

        for (int i = 0; i < size; i++)
        {
            student_t tmp = get_student_by_pos(src, i);
            if (strstr(tmp.surname, sub_surname) == tmp.surname)
            {
                put_student_by_pos(dst, pos, tmp);
                pos++;
            }
        }

        // ??????
        // if (pos == 0)
        //     rc = ERR_DATA;
    }
    else
    {
        rc = ERR_DATA;
    }

    return rc;
}

// удаляет запись из файла, сдвигая остальные назад
int delete_student_by_pos(FILE *f, int pos)
{
    int rc = OK;
    int size = size_of_file(f) / sizeof(student_t);

    for (int i = pos + 1; rc == OK && i < size; i++)
    {
        student_t tmp = get_student_by_pos(f, i);
        rc = put_student_by_pos(f, i - 1, tmp);
    }

    return rc;
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

double count_average_grade(FILE *f)
{
    int size = size_of_file(f) / sizeof(student_t);
    double average = 0;

    if (size != 0)
    {
        for (int i = 0; i < size; i++)
        {
            student_t tmp = get_student_by_pos(f, i);
            average += average_grade(tmp);
        }
        average /= size;
    }
    
    return average;
}

int delete_students(FILE *f)
{
    int rc = OK;

    if (is_typed_file(f))
    {
        double average_average_grade = count_average_grade(f);
        int size = size_of_file(f) / sizeof(student_t);
        int deleted = 0;

        for (int i = 0; rc == OK && i < size - deleted; i++)
        {
            student_t tmp = get_student_by_pos(f, i);
            if (average_grade(tmp) < average_average_grade)
            {
                rc = delete_student_by_pos(f, i);
                deleted++;
                i--;
            }
        }

        ftruncate(fileno(f), (size - deleted) * sizeof(student_t));

        // ?????
        if (size - deleted == 0)
            rc = ERR_DATA
    }
    else
    {
        rc = ERR_DATA;
    }
    
    return rc;
}

// размер в байтах
long size_of_file(FILE *f)
{
    long current = ftell(f);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, current, SEEK_SET);
    return size;
}

// является ли файл массивом объектов, так называемый "типизированный файл"
int is_typed_file(FILE *f)
{
    long size_bytes = size_of_file(f);
    return size_bytes != 0 && size_bytes % sizeof(student_t) == 0;
}