#include <stdio.h>
#include <stddef.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define MAX_INPUT_AMOUNT 10

int input_array(int arr[], int *size);

double count_average_negative(int arr[], int size, int *exit_code);

int main(void)
{
    int exit_code = OK;
    int rc = 0;

    int nums[MAX_INPUT_AMOUNT] = { 0 };
    int n = 0;

    rc = input_array(nums, &n);
   
    if (rc)
    {
        double result;
        result = count_average_negative(nums, n, &exit_code);

        if (exit_code == OK)
            printf("%lf", result);
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

    if (*size < 0 || *size > MAX_INPUT_AMOUNT)
        rc = 0;

    if (rc == 1)
        for(int i = 0; i < *size && rc == 1; ++i)
            rc = scanf("%d", arr + i);
    
    return rc;
}

double count_average_negative(int arr[], int size, int *exit_code)
{
    double result = 0;
    int negative_amount = 0;

    for (int i = 0; i < size; ++i)
    {
        if (arr[i] < 0)
        {
            result += arr[i];
            ++negative_amount;
        }
    }

    if (negative_amount != 0)
    {
        result /= negative_amount;
    }
    else
    {
        *exit_code = ERR_DATA;
    }

    return result;
}