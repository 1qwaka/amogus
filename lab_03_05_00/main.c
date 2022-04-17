#include <stdio.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define MAX_ROWS 10
#define MAX_COLS 10

int correct_size(int size, int max_value);

int input_matrix(int **matrix, int *rows, int *cols);

void print_matrix(int **matrix, int rows, int cols);

void transform(int **matrix, int *from_buffer, int rows, int cols);

int fill_array(int *arr, int *arr_size, int **matrix, int rows, int cols);

void put_array_in_matrix(int *arr, int **matrix, int rows, int cols);

int is_prime(int value);

void reverse_array(int *array, int size);

int main(void)
{
    int exit_code = OK;

    int cols = 0, rows = 0;
    int buffer[MAX_ROWS][MAX_COLS] = { 0 }; 
    int *matrix[MAX_COLS] = { 0 };

    int arr_size = 0;
    int result_array[MAX_ROWS * MAX_COLS] = { 0 };

    transform(matrix, &buffer[0][0], MAX_ROWS, MAX_COLS);

    exit_code = input_matrix(matrix, &rows, &cols);

    if (exit_code == OK)
    {   
        exit_code = fill_array(result_array, &arr_size, matrix, rows, cols);

        if (exit_code == OK)
        {
            reverse_array(result_array, arr_size);
            put_array_in_matrix(result_array, matrix, rows, cols);
            print_matrix(matrix, rows, cols);
        }
        else
        {
            exit_code = ERR_DATA;
        }
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

int fill_array(int *arr, int *arr_size, int **matrix, int rows, int cols)
{
    int rc = OK;
    *arr_size = 0;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (is_prime(matrix[i][j]))
                arr[(*arr_size)++] = matrix[i][j];
        }
    }

    if (*arr_size == 0)
        rc = ERR_DATA;

    return rc;
}

void put_array_in_matrix(int *arr, int **matrix, int rows, int cols)
{
    int cur_pos = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (is_prime(matrix[i][j]))
                matrix[i][j] = arr[cur_pos++];
        }
    }
}

int is_prime(int value)
{
    int result = 1;
    for (int i = 2; i * i < value + 1 && result; ++i)
        if (value % i == 0)
            result = 0;
  
    if (value == 0)
        result = 0;

    return result;
}

void reverse_array(int *arr, int size)
{
    int tmp = 0;
    for (int i = 0; i < size / 2; ++i)
    {
        tmp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = tmp;
    }
}