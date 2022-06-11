#include <stdlib.h>
#include <time.h>
#include "fill_random.h"
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
