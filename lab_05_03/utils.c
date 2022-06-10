#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "utils.h"


int fill_random_numbers(FILE *f, int amount)
{
    int rc = true;
    num_t tmp = 0;

    srand(time(NULL));
    for (int i = 0; i < amount && rc; i++)
    {
        tmp = rand() - RAND_MAX / 2;
        rc = fwrite(&tmp, sizeof(tmp), 1, f) == 1;
    }
    
    if (ferror(f))
        rc = ERR_IO;
    else
        rc = OK;
    
    return rc;
}

int print_nums(FILE *f)
{
    int rc = OK;
    
    if (is_typed_file(f))
    {
        num_t tmp = 0;
        while (fread(&tmp, sizeof(tmp), 1, f) == 1)
            printf("%d ", tmp);
    
        if (ferror(f))
            rc = ERR_IO;
    }
    else
    {
        rc = ERR_DATA;
    }
    
    return rc;
}

int sort_file(FILE *f)
{
    int rc = true;
    
    if (is_typed_file(f))
    {
        long size = size_of_file(f) / sizeof(num_t);

        for (int i = 0; rc && i < size; i++)
            for (int j = 0; rc && j < size - i - 1; j++)
            {
                num_t cur = 0, next = 0;
                rc = get_number_by_pos(f, j, &cur) && get_number_by_pos(f, j + 1, &next);
                if (rc && cur > next)
                    rc = put_number_by_pos(f, j, next) && put_number_by_pos(f, j + 1, cur);
            }
    }
    else
    {
        rc = ERR_DATA;
    }

   
    return rc;
}

bool get_number_by_pos(FILE *f, int pos, num_t *number)
{
    fseek(f, sizeof(num_t) * pos, SEEK_SET);
    return fread(number, sizeof(num_t), 1, f) == 1;
}

bool put_number_by_pos(FILE *f, int pos, num_t number)
{
    fseek(f, sizeof(number) * pos, SEEK_SET);
    return fwrite(&number, sizeof(number), 1, f) == 1;
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

// проверяет является ли файл массивом чисел, так называемый "типизированный файл"
bool is_typed_file(FILE *f)
{
    long size_bytes = size_of_file(f);    
    return size_bytes != 0 && size_bytes % sizeof(num_t) == 0;
}