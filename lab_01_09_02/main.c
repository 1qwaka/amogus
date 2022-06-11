#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define ERR_IN 1
#define ERR_DATA 2
#define FLOAT_ERR 1e-6

int main(void)
{
    double x = 0, sum = 0;
    long i = 0;
    short rc = 0;
    int exit_code = 0;

    while (1 == (rc = scanf("%lf", &x)) && x >= 0)
    {
        sum += sqrt(1 + i + x);
        ++i;
    }

    if (rc != 1)
        exit_code = ERR_IN;
    // введено 0 положительных элементов
    else if (fabs(sum) < FLOAT_ERR)
        exit_code = ERR_DATA;
    else
    {
        sum /= i;
        printf("%lf", sum);
    }

    return exit_code;
}
