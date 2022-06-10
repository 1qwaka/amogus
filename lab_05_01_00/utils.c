#include <stdbool.h>
#include <stdio.h>
#include "utils.h"


int process(FILE *f, int *result)
{
    int rc = OK;
    int tmp = 0;
    // bool found_negative = false;
    bool found_any_max = false;
    int max = -1;
    int prev_num = 0;

    if (fscanf(f, "%d", &prev_num) == 1)
    {
        while (fscanf(f, "%d", &tmp) == 1)
        {
            if (prev_num < 0 && tmp > 0 && tmp > max)
            {
                max = tmp;
                found_any_max = true;
            }
            prev_num = tmp;
        }

        if (!found_any_max)
            rc = ERR_DATA;
        else
            *result = max;
    }
    else
    {
        rc = ERR_INPUT;
    }

    return rc;
}