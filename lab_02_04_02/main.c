#include <stdio.h>
#include <stddef.h>
#include <math.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2
#define ERR_SPEC  100

#define MAX_INPUT_AMOUNT 10
#define FLOAT_ERR        1e-6

int input_array(int *arr, int *size);

void print_array(int *arr, int size);

void bubble_sort(int *arr, int size);

void swap(int *a, int *b);

int main(void)
{
    int exit_code = OK;
    int rc;

    int nums[MAX_INPUT_AMOUNT] = { 0 };
    int n = 0;

    rc = input_array(nums, &n);
   
    if (rc && n > 0)
    {
        int result[MAX_INPUT_AMOUNT] = { 0 };

        for (int i = 0; i < n; ++i)
            result[i] = nums[i];
        
        bubble_sort(result, n);

        print_array(result, n);

        if (rc == ERR_SPEC)
            exit_code = ERR_SPEC;
    }
    else if (n == 0) 
    {
        exit_code = ERR_DATA;
    }
    else
    {
        exit_code = ERR_INPUT;
    }

    return exit_code;
}

int input_array(int *arr, int *size)
{
    int i = 0;
    int rc = 0;
    while ((rc = scanf("%d", arr + i)) == 1 && *size < MAX_INPUT_AMOUNT)
    {
        ++i;
        ++(*size);
    }

    // если массив заполнился и пользователь ввел еще один валидный элемент
    if (rc == 1 && *size == MAX_INPUT_AMOUNT)
        rc = ERR_SPEC;
    // успешно если хотя бы первый элемент введен правильно
    else 
        rc = *size > 0;

    return rc;
}

void print_array(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
        printf("%d ", arr[i]);
    printf("%d", arr[size - 1]);
}

void bubble_sort(int *arr, int size)
{
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr + j, arr + j + 1);
}

void swap(int *a, int *b)
{
    int tmp = 0;
    tmp = *a;
    *a = *b;
    *b = tmp;
}