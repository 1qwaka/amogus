/*
 * выбранный тип данных - int32_t
 * алгоритм сортировки - сортировка пузырьком
 * направление сортировки - по возрастанию
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "print.h"
#include "sort.h"
#include "fill_random.h"

int main(int argc, char *argv[])
{
    int exit_code = OK;
    
    if (argc == 4 && strcmp("c", argv[1]) == 0)
    {
        FILE *f = fopen(argv[3], "wb");
        exit_code = fill_random_numbers(f, atoi(argv[2]));
        fclose(f);
    } 
    else if (argc == 3 && strcmp("p", argv[1]) == 0)
    {
        FILE *f = fopen(argv[2], "rb+");
        if (f != NULL)
        {
            exit_code = print_nums(f);
            fclose(f);
        }
        else
        {
            exit_code = ERR_IO;
        }
    } 
    else if (argc == 3 && strcmp("s", argv[1]) == 0)
    {
        FILE *f = fopen(argv[2], "rb+");
        if (f != NULL)
        {
            exit_code = sort_file(f);
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
