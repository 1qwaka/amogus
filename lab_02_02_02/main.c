#include <stdio.h>
#include <stddef.h>
#include <math.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define MAX_INPUT_AMOUNT 10

int input_array(int arr[], int *size);

void print_array(int arr[], int size);

void form_array(int from[], int size_from, int to[], int *size_to);

int correct_number(int n);

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

        form_array(nums, n, result, &result_size);
        // printf("after function size=%d\n", result_size);

        if (result_size > 0)
            print_array(result, result_size);
        else
            exit_code = ERR_DATA;
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
        for (int i = 0; i < *size && rc == 1; ++i)
            rc = scanf("%d", arr + i);
    
    return rc;
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
        printf("%d ", arr[i]);
    printf("%d", arr[size - 1]);
}

void form_array(int from[], int size_from, int to[], int *size_to)
{
    *size_to = 0;
    for (int i = 0; i < size_from; ++i)
        if (correct_number(from[i])){
            // printf("correct %d \n", from[i]);
            to[(*size_to)++] = from[i];
            // printf("size == %d\n", *size_to);
        }
    // printf("in end size == %d\n", *size_to);
}

int correct_number(int n)
{
    int first_digit = n % 10;
    int last_digit = first_digit;

    int i = 0;
    do {
        last_digit = (n % (int)pow(10, i + 1)) / (int)pow(10, i);
        ++i;
    } while (n / (int)pow(10, i) != 0);

    // printf("n = %d : last = %d : first = %d\n", n, last_digit, first_digit);
    return first_digit == last_digit;
}