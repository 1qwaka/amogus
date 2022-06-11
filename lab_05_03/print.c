#include "print.h"
#include "utils.h"

int print_nums(FILE *f)
{
    int rc = OK;
    num_t tmp = 0;
    
    if (is_typed_file(f))
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
