#include <stdio.h>
#include <stdbool.h>
#include "utils.h"

int main(void)
{
    int exit_code = OK;
    
    int max = 0;
    exit_code = process(stdin, &max);
    if (exit_code == OK)
        printf("%d", max);

    return exit_code;
}
