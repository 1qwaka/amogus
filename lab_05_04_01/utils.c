#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"


int print_students(FILE *f)
{
    int rc = OK;
    
    if (is_typed_file(f))
    {
        long size = size_of_file(f) / sizeof(student_t);
        fseek(f, 0, SEEK_SET);
        // while (fread(&tmp, sizeof(tmp), 1, f) == 1)
            // print_student(tmp);
        
        student_t tmp = { 0 };
        for (int i = 0; rc == OK && i < size; i++)
        {
            rc = get_student_by_pos(f, i, &tmp);
            if (rc == OK)
                print_student(tmp);
        }
        // if (ferror(f))
        //     rc = ERR_IO;
    }
    else
    {
        rc = ERR_DATA;
    }
    
    return rc;
}

void print_student(student_t student)
{
    printf("%s\n%s\n", student.surname, student.name);
    for (int i = 0; i < SUBJECTS_AMOUNT; i++)
        printf("%u\n", student.grades[i]);
    // printf("\n");    
}

int sort_file(FILE *f)
{
    int rc = OK;

    if (is_typed_file(f))
    {
        long size = size_of_file(f) / sizeof(student_t);
        for (int i = 0; rc == OK && i < size; i++)
            for (int j = 0; rc == OK && j < size - i - 1; j++)
            {
                student_t cur = { 0 }, next = { 0 };
                rc = get_student_by_pos(f, j, &cur);
                if (rc == OK)
                    rc = get_student_by_pos(f, j + 1, &next);

                if (rc == OK && compare(next, cur))
                {
                    rc = put_student_by_pos(f, j, next);
                    if (rc == OK)
                        put_student_by_pos(f, j + 1, cur);
                    // printf("swapped pos1=%d pos2=%d \n1. %s %s\n2. %s %s\n", j, j + 1, cur.surname, cur.name, next.surname, next.name);
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
    int result = strcmp(big.surname, small.surname);
    // printf("surnamre %s bigger %s: %d\n", big.surname, small.surname, result);
    if (result == 0)
        result = strcmp(big.name, small.name);

    return result > 0;
}

int get_student_by_pos(FILE *f, int pos, student_t *student)
{
    fseek(f, sizeof(student_t) * pos, SEEK_SET);
    return fread(student, sizeof(student_t), 1, f) == 1 ? OK : ERR_GET_STUDENT;
}

int put_student_by_pos(FILE *f, int pos, student_t student)
{
    fseek(f, sizeof(student) * pos, SEEK_SET);
    int rc = fwrite(&student, sizeof(student), 1, f) == 1 ? OK : ERR_PUT_STUDENT;
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
            student_t tmp = { 0 };
            get_student_by_pos(src, i, &tmp);
            if (strstr(tmp.surname, sub_surname) == tmp.surname)
            {
                put_student_by_pos(dst, pos, tmp);
                pos++;
            }
        }

        if (pos == 0)
            rc = ERR_DATA;
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

    student_t tmp = { 0 };
    for (int i = pos + 1; rc == OK && i < size; i++)
    {
        rc = get_student_by_pos(f, i, &tmp);
        if (rc == OK)
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

int count_average_grade(FILE *f, double *result)
{
    int rc = OK;
    int size = size_of_file(f) / sizeof(student_t);
    double average = 0;

    if (size != 0)
    {
        for (int i = 0; rc == OK && i < size; i++)
        {
            student_t tmp = { 0 };
            rc = get_student_by_pos(f, i, &tmp);
            average += average_grade(tmp);
        }
        average /= size;
    }
    
    *result = average;
    return rc;
}

int delete_students(FILE *f)
{
    int rc = OK;

    if (is_typed_file(f))
    {
        double average_average_grade = 0;
        rc = count_average_grade(f, &average_average_grade);
        int size = size_of_file(f) / sizeof(student_t);
        int deleted = 0;

        // printf("avg file: %lf\n", average_average_grade);
        // printf("students amount: %d\n", size);

        for (int i = 0; rc == OK && i < size - deleted; i++)
        {
            student_t tmp = { 0 };
            rc = get_student_by_pos(f, i, &tmp);

            if (rc == OK && average_grade(tmp) < average_average_grade)
            {
                rc = delete_student_by_pos(f, i);
                // printf("delete: '%s %s' avg grade: %lf\n", tmp.surname, tmp.name, average_grade(tmp));
                if (rc == OK)
                {
                    deleted++;
                    i--;
                }
            }
        }

        rewind(f);
        if (rc == OK)
            rc = ftruncate(fileno(f), (size - deleted) * sizeof(student_t)) == 0 ? OK : ERR_TRUNCATE;

        // printf("total deleted: %d\nfile truncated from %d (%zu bytes) to %d (%zu bytes)\n", deleted, size,
                                                                                        // size * sizeof(student_t),
                                                                                        // size - deleted,
                                                                                        // (size - deleted) * sizeof(student_t));
        // printf("rc: %d\nfile length bytes: %ld\n", rc, size_of_file(f));
        // print_students(f);
        // ?????
        // if (size - deleted == 0)
        //     rc = ERR_DATA;
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