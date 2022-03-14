#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define ERR_IN 1
#define ERR_DATA 2
#define FLOAT_ERR 1e-6

void print_binary(uint32_t i);

int main(void)
{
    long long a = 0x00000000, n = 0;
    short rc = 0;
    int exit_code = 0;

    rc = scanf("%lld%lld", &a, &n);
    if (rc != 2)
    {
        printf("Error: invalid input");
        exit_code = ERR_IN;
    }
    else if (n < 0)
    {
        printf("Error: invalid data");
        exit_code = ERR_DATA;
    }
    else
    {
        uint32_t result_a = (uint32_t)a;
        uint32_t result = (result_a << n) | (result_a >> (32 - n));
        printf("Result: ");
        print_binary(result);
    }

    return exit_code;
}

void print_binary(uint32_t n)
{
    short size = 32 - 1;

    for (short i = size; i > -1; i--)
    {
        printf("%u", (n & (1 << i)) >> i);
    }
}
