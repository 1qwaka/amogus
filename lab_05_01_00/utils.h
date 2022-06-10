#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>

#define OK        0
#define ERR_INPUT -1
#define ERR_DATA  -2

int process(FILE *f, int *result);

#endif