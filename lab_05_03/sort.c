#include "utils.h"

int sort_file(FILE *f)
{
    int rc = OK;
    
    if (is_typed_file(f))
    {
        long size = size_of_file(f) / sizeof(num_t);
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