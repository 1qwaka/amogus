#include <stdio.h>
#include <math.h>

#define ERR_IN 1
#define ERR_DATA 2
#define FLOAT_ERR 1e-6

double approximate_exp(double x, double eps);

int main(void)
{
    double x = 0, eps = 0, absolute_error = 0, relative_error = 0;
    short rc = 0;
    int exit_code = 0;

    rc = scanf("%lf%lf", &x, &eps);
    if (rc != 2)
    {
        exit_code = ERR_IN;
    }
    else if (eps <= 0 || eps > 1)
    {
        exit_code = ERR_DATA;
    }
    else
    {
        double relative_value = 0, absolute_value = 0;
        absolute_value = exp(x);
        relative_value = approximate_exp(x, eps);
        absolute_error = fabs(absolute_value - relative_value);
        relative_error = absolute_error / fabs(absolute_value);
        

        printf("%lf %lf %lf %lf", relative_value, absolute_value, absolute_error, relative_error);
    }

    return exit_code;
}

double approximate_exp(double x, double eps)
{
    double value = 1;
    double cur = 1;
    long i = 1;

    while (fabs(cur *= x / i) >= eps)
    {
        value += cur;
        i++;
    }

    return value;
}