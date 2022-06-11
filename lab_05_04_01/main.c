#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student_utils.h"

int main(int argc, char *argv[])
{
    int exit_code = OK;

    /*
    FILE *f = fopen("students.bin", "wb");

    student_t andrey = { "andrey", "vickhodsev", {5, 5, 5, 4}};
    put_student_by_pos(f, 0, andrey);

    student_t dima = { "dmitriy", "popov", {2, 4, 3, 3}};
    put_student_by_pos(f, 1, dima);

    student_t sergey = { "sergey", "vickhodsev", {5, 5, 5, 5}};
    put_student_by_pos(f, 2, sergey);

    student_t alex = { "andrey", "bell", {4, 5, 5, 4}};
    put_student_by_pos(f, 3, alex);

    printf("sizeof: %zu\n", sizeof(student_t));

    fclose(f);
    */
    
    if (argc == 3 && strcmp("sb", argv[1]) == 0)
    {
        FILE *f = fopen(argv[2], "rb+");
        if (f != NULL)
        {
            exit_code = sort_file(f);
            if (exit_code == OK)
                exit_code = print_students(f);
            fclose(f);
        }
        else
        {
            exit_code = ERR_NO_FILE;
        }
    } 
    else if (argc == 5 && strcmp("fb", argv[1]) == 0)
    {
        FILE *src = fopen(argv[2], "rb");
        FILE *dst = fopen(argv[3], "wb");

        if (src != NULL && src != NULL)
        {
            exit_code = print_appropriate_students(src, dst, argv[4]);
            fclose(src);
            fclose(dst);
        }
        else
        {
            if (src != NULL)
                fclose(src);
            if (dst != NULL)
                fclose(dst);

            exit_code = ERR_IO;
        }
    } 
    else if (argc == 3 && strcmp("db", argv[1]) == 0)
    {
        FILE *f = fopen(argv[2], "rb+");
        if (f != NULL)
        {
            exit_code = delete_students(f);
            fclose(f);
        }
        else
        {
            exit_code = ERR_IO;
        }
    }
    else
    {
        exit_code = ERR_ARGS;
    }

    return exit_code;
}
