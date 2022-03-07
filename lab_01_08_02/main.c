#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define ERR_IN 1
#define ERR_DATA 2
#define FLOAT_ERR 1e-6

void print_binary(uint32_t i);

// unsigned long cycle_shift(unsigned long i);

int main(void)
{
    long long a = 0xFF00F000, n = -4;
    short rc = 0;
    int exit_code = 0;

    rc = scanf("%lld%lld", &a, &n);
    // printf("hello %d ", 1 << 8);
    // rc = 2;
    if (rc != 2)
    {
        printf("Error: invalid input");
        exit_code = ERR_IN;
    }
    else if (a < 0 || a > (1ll << 32) || n < 0)
    {
        // printf("err data %lu ", sizeof (unsigned long));
        printf("Error: invalid data");
        exit_code = ERR_DATA;
    }
    else
    {
        uint32_t result_a = (uint32_t)a;
        uint32_t result = (result_a << n) | (result_a >> (32 - n));

        // printf("result %ld", result);
        // print_binary(result_a);
        // printf("\n======================\n");
        printf("Result: ");
        print_binary(result);
    }

    return exit_code;
}

void print_binary(uint32_t n)
{
    // short found_first = 0;
    short size = 32 - 1;

    for (short i = size; i > -1; i--)
    {
        // printf("i = %d\n", i);
        // printf("N = %u\n", n);
        printf("%u", (n & (1 << i)) >> i);

        // printf("%d: %ld\n", i, n >> i);
        // if (!found_first && (n >> i)) 
        //     found_first = 1;
        
        // if (found_first)
        // {
        //     printf("%u", (n & (1 << i)) >> i);
        // }
    }
    
}