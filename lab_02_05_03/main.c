#include <stdio.h>
#include <stddef.h>
#include <limits.h>


#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define MAX_INPUT_AMOUNT 10
#define FLOAT_ERR        1e-6

int input_array(int *pa, int **pb);

void print_array(int *pa, int *pb);

int count_value(int *pa, int *pb, int *exit_code);

int main(void)
{
    int exit_code = OK;
    int rc;

    int nums[MAX_INPUT_AMOUNT] = { 0 };
    int *pa = nums, *pb = nums;

    rc = input_array(pa, &pb);
   
    if (rc)
    {
        int result = count_value(pa, pb, &exit_code);
       
        if (exit_code == OK)
            printf("%d", result);
        else
            exit_code = ERR_DATA;
    }
    else
    {
        exit_code = ERR_INPUT;
    }

    return exit_code;
}

int input_array(int *pa, int **pb)
{
    int size = 0;
    int rc = scanf("%d", &size);

    if (size <= 0 || size > MAX_INPUT_AMOUNT)
        rc = 0;

    *pb = pa + size;

    while (pa < *pb && rc == 1)
        rc = scanf("%d", pa++);           

    return rc > 0;
}

void print_array(int *pa, int *pb)
{
    while (pa < pb - 1)
        printf("%d ", *pa++);
    printf("%d", *pa);
}

int count_value(int *pa, int *pb, int *exit_code)
{
    int result = 0;
    if (pb - pa < 2)
    {
        *exit_code = ERR_DATA;
    }
    else
    {
        int prev = *pa++;
        int min = prev * *pa;
        int tmp = 0;
        prev = *pa++;

        while (pa < pb)
        {
            if ((tmp = prev * *pa) < min)
                min = tmp;
            prev = *pa++;
        }

        result = min;
        *exit_code = OK;
    }
    return result;
}