#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "utils.h"


int fill_random_numbers(FILE *f, int amount)
{
    int rc = 1;
    num_t tmp = 0;

    srand(time(NULL));
    for (int i = 0; i < amount && rc; i++)
    {
        tmp = rand() - RAND_MAX / 2;
        rc = fwrite(&tmp, sizeof(tmp), 1, f) == 1;
    }
    
    if (!rc)
        rc = OK;
    else
        rc = ERR_IO;
    
    return rc;
}

int print_nums(FILE *f)
{
    int rc = OK;
    num_t tmp = 0;
    
    long size_bytes = size_of_file(f);
    if (size_bytes != 0 && size_bytes % sizeof(num_t) == 0)
    {
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
    int rc = OK;
    long size_bytes = size_of_file(f);

    if (size_bytes != 0 && size_bytes % sizeof(num_t) == 0)
    {
        long size = size_bytes / sizeof(num_t);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size - i - 1; j++)
            {
                num_t cur = get_number_by_pos(f, j);
                num_t next = get_number_by_pos(f, j + 1);
                if (cur > next)
                {
                    put_number_by_pos(f, j, next);
                    put_number_by_pos(f, j + 1, cur);
                }
            }    
    }
    else
    {
        rc = ERR_DATA;
    }

   
    return rc;
}

num_t get_number_by_pos(FILE *f, int pos)
{
    num_t result = 0;
    fseek(f, sizeof(result) * pos, SEEK_SET);
    fread(&result, sizeof(result), 1, f);
    return result;
}

int put_number_by_pos(FILE *f, int pos, num_t number)
{
    fseek(f, sizeof(number) * pos, SEEK_SET);
    int rc = fwrite(&number, sizeof(number), 1, f) == 1 ? OK : ERR_IO;
    return rc;
}

long size_of_file(FILE *f)
{
    long current = ftell(f);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, current, SEEK_SET);
    return size;
}
