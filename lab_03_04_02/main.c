#include <stdio.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define MAX_ROWS 10
#define MAX_COLS 10
#define REQUIRED_DIGIT 5

int correct_size(int size, int max_value);

int input_matrix(int **matrix, int *rows, int *cols);

void print_matrix(int **matrix, int rows, int cols);

void transform(int **matrix, int *from_buffer, int rows, int cols);

int find_element(int **matrix, int rows, int cols, int *return_value);

int main(void)
{
    int exit_code = OK;

    int cols = 0, rows = 0;
    int buffer[MAX_ROWS][MAX_COLS] = { 0 }; 
    int *matrix[MAX_COLS] = { 0 };

    transform(matrix, &buffer[0][0], MAX_ROWS, MAX_COLS);

    exit_code = input_matrix(matrix, &rows, &cols);

    if (exit_code == OK)
    {   
        int result = 0;
        exit_code = find_element(matrix, rows, cols, &result);

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

int correct_size(int size, int max_value)
{
    return size > 0 && size <= max_value;
}

int input_matrix(int **matrix, int *rows, int *cols)
{
    int rc = OK;

    rc = scanf("%d%d", rows, cols);
    rc = rc == 2 &&
        correct_size(*rows, MAX_ROWS) &&
        correct_size(*cols, MAX_COLS) 
        ? OK : ERR_INPUT;

    if (rc == OK)
    {
        rc = 1;
        for (int i = 0; i < *rows && rc == 1; ++i)
        {
            for (int j = 0; j < *cols && rc == 1; ++j)
            {
                rc = scanf("%d", &matrix[i][j]);
            }
        }

        if (rc == 1)
            rc = OK;
        else
            rc = ERR_INPUT;
    }

    return rc;
}

void print_matrix(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void transform(int **matrix, int *from_buffer, int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
        matrix[i] = from_buffer + i * cols;
}

int int_abs(int value)
{
    if (value < 0)
        value *= -1;
    return value;
}

int find_element(int **matrix, int rows, int cols, int *return_value)
{
    int rc = OK;

    if (rows == cols && rows > 1)
    {
        *return_value = 0;
        int any_found = 0;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = cols - i; j < cols; ++j)
            {
                if (int_abs(matrix[i][j]) % 10 == REQUIRED_DIGIT && 
                    (*return_value < matrix[i][j] || any_found == 0))
                {
                    *return_value = matrix[i][j];
                    any_found = 1;
                }
            }
        }

        if(!any_found)
            rc = ERR_DATA;
    }
    else
    {
        rc = ERR_DATA;
    }
    
    return rc;
}

int array_mul(int *arr, int size)
{
    int result = 1;
    for (int i = 0; i < size; ++i)
        result *= arr[i];

    return result;   
}

void copy_array(int *src, int *dst, int size)
{
    for (int i = 0; i < size; ++i)
        dst[i] = src[i];   
}

void switch_arrrays(int *arr1, int *arr2, int size)
{
    int tmp_array[MAX_COLS] = { 0 };
    copy_array(arr1, tmp_array, size);
    copy_array(arr2, arr1, size);
    copy_array(tmp_array, arr2, size);
}