#include <stdio.h>
#include <stdbool.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    int exit_code = OK;
    
    if (argc == 2)
    {
        FILE *f = fopen(argv[1], "r");
        if (f != NULL)
        {
            int result = 0;
            exit_code = correct_3sigma_rule(f, &result);
            if (exit_code == OK)
                printf("%d", result);
        }
        else
        {
            exit_code = ERR_IO;
        }
    }
    else
    {
        exit_code = ERR_ARGS;
    }

    return exit_code;
}
