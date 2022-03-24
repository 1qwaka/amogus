#include <stdio.h>
#include <stddef.h>
#include <math.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define MAX_INPUT_AMOUNT 10
#define FLOAT_ERR        1e-6

int input_array(int arr[], int *size);

void print_array(int arr[], int size);

void delete_full_squares(int from[], int size_from, int to[], int *size_to);

int is_full_square(int n);

int main(void)
{
    int exit_code = OK;
    int rc;

    int nums[MAX_INPUT_AMOUNT] = { 0 };
    int n = 0;

    rc = input_array(nums, &n);
   
    if (rc)
    {
        int result[MAX_INPUT_AMOUNT] = { 0 };
        int result_size = 0;

        delete_full_squares(nums, n, result, &result_size);

        if (result_size > 0)
            print_array(result, result_size);
    }
    else
    {
        exit_code = ERR_INPUT;
    }

    return exit_code;
}

int input_array(int arr[], int *size)
{
    int rc = scanf("%d", size);

    if (*size <= 0 || *size > MAX_INPUT_AMOUNT)
        rc = 0;

    if (rc == 1)
        for (int i = 0; i < *size && rc == 1; ++i)
            rc = scanf("%d", arr + i);
    
    return rc > 0;
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
        printf("%d ", arr[i]);
    printf("%d", arr[size - 1]);
}

void delete_full_squares(int from[], int size_from, int to[], int *size_to)
{
    *size_to = 0;
    for (int i = 0; i < size_from; ++i)
        if (!is_full_square(from[i]))
            to[(*size_to)++] = from[i];
}

int is_full_square(int n)
{
    double square = sqrt(n);
    return square - (int)square < FLOAT_ERR;
}