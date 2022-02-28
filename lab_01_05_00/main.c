#include <stdio.h>
#include <math.h>

#define ERR_IN 1
#define or ||

int main(void)
{
    long a = 0;
    long n = 0;
    long long result = 0;
    short rc = 0;
    short exit_code = 0;

    rc = scanf("%ld%ld", &a, &n);

    if (rc != 2 or n < 0) {
        exit_code = ERR_IN;
    } else {
        result = pow(a, n);
        printf("%lld", result);
    }

    return exit_code;
}
