#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <inttypes.h>

#define OK        0
#define ERR_IO    1
#define ERR_DATA  2
#define ERR_ARGS  3

typedef int32_t num_t;

int fill_random_numbers(FILE *f, int amount);

int print_nums(FILE *f);

int sort_file(FILE *f);

num_t get_number_by_pos(FILE *f, int pos);

int put_number_by_pos(FILE *f, int pos, num_t number);

long size_of_file(FILE *f);

#endif