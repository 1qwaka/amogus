#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>

#define OK        0
#define ERR_IO    1
#define ERR_DATA  2
#define ERR_ARGS  3

int correct_3sigma_rule(FILE *f, int *result);

#endif