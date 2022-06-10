#include <stdbool.h>
#include <stdio.h>
#include "utils.h"


int process(FILE *f, int *result)
{
    int rc = OK;
    int tmp = 0;
    bool found_negative = false;
    bool found_any_max = false;
    int max = 0;

    rc = fscanf(f, "%d", &max) == 1 ? OK : ERR_INPUT;
    
    while (rc == OK && fscanf(f, "%d", &tmp) == 1)
    {
        if (!found_negative && tmp < 0)
            found_negative = true;
        
        if (found_negative && tmp > 0 && tmp > max)
        {
            max = tmp;
            found_any_max = true;
        }
    }

    if (rc == OK && !found_any_max)
        rc = ERR_DATA;
    else if (rc == OK)
        *result = max;
    

    return rc;
}