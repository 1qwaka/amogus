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

int process_matrix(int **matrix, int rows, int cols);

int array_mul(int *arr, int size);

void copy_array(int *src, int *dst, int size);

void switch_arrrays(int **arr1, int **arr2);

int main(void)
{
    int exit_code = OK;

    int cols = 0, rows = 0;
    int buffer[MAX_ROWS][MAX_COLS] = { 0 }; 
    int *matrix[MAX_COLS] = { 0 };

    transform(matrix, buffer[0], MAX_ROWS, MAX_COLS);

    exit_code = input_matrix(matrix, &rows, &cols);

    if (exit_code == OK)
    {
        exit_code = process_matrix(matrix, rows, cols);
        if (exit_code == OK)
        {
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

int process_matrix(int **matrix, int rows, int cols)
{
    int rc = OK;

    // пузырьком с флагом
    for (int i = 0; i < rows; ++i)
    {
        int any_switched = 1;
        for (int j = 0; j < rows - i - 1 && any_switched == 1; ++j)
        {
            if (array_mul(matrix[j], cols) > array_mul(matrix[j + 1], cols))
            {
                switch_arrrays(matrix + j, matrix + j + 1);
                any_switched = 1;
            }
        }
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

void switch_arrrays(int **arr1, int **arr2)
{
    int *tmp = *arr1;
    *arr1 = *arr2;
    *arr2 = tmp;
}