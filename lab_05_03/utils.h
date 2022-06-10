#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#define OK        0
#define ERR_IO    1
#define ERR_DATA  2
#define ERR_ARGS  3

typedef int32_t num_t;

int fill_random_numbers(FILE *f, int amount);

int print_nums(FILE *f);

int sort_file(FILE *f);

bool get_number_by_pos(FILE *f, int pos, num_t *number);

bool put_number_by_pos(FILE *f, int pos, num_t number);

long size_of_file(FILE *f);

bool is_typed_file(FILE *f);