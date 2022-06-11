#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "utils.h"


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

// является ли файл массивом чисел, так называемый "типизированный файл"
int is_typed_file(FILE *f)
{
    long size_bytes = size_of_file(f);
    return size_bytes != 0 && size_bytes % sizeof(num_t) == 0;
}