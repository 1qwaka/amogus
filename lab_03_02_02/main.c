#include <stdio.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define MAX_ROWS 10
#define MAX_COLS 10
#define RESULT_ROWS MAX_ROWS * 2
#define REQUIRED_SUMS 2
#define FILLER -1

int correct_size(int size, int max_value);

int input_matrix(int **matrix, int *rows, int *cols);

void print_matrix(int **matrix, int rows, int cols);

void transform(int **matrix, int *from_buffer, int rows, int cols);

int process_matrix(int **result_matrix, int *result_rows, int **matrix, int rows, int cols);

int digits_sum(int value);

void copy_array(int *src, int *dst, int size);

void fill_array(int *arr, int size, int value);

int main(void)
{
    int exit_code = OK;

    int cols = 0, rows = 0, result_rows = 0;
    int buffer[MAX_ROWS][MAX_COLS] = { 0 }; 
    int *matrix[MAX_COLS] = { 0 };
    int result_buffer[RESULT_ROWS][MAX_COLS] = { 0 }; 
    int *result_matrix[MAX_COLS] = { 0 };

    transform(matrix, &buffer[0][0], MAX_ROWS, MAX_COLS);
    transform(result_matrix, &result_buffer[0][0], RESULT_ROWS, MAX_COLS);

    exit_code = input_matrix(matrix, &rows, &cols);

    if (exit_code == OK)
    {
        exit_code = process_matrix(result_matrix, &result_rows, matrix, rows, cols);
        if (exit_code == OK)
        {
            print_matrix(result_matrix, result_rows, cols);
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

int process_matrix(int **result_matrix, int *result_rows, int **matrix, int rows, int cols)
{
    int rc = OK;
    *result_rows = 0;

    for (int i = 0; i < rows; ++i)
    {
        int not_even_sums = 0;
        for (int j = 0; j < cols; ++j)
        {
            not_even_sums += digits_sum(matrix[i][j]) % 2 == 1;
        }

        if (not_even_sums >= REQUIRED_SUMS)
        {
            fill_array(result_matrix[*result_rows], cols, FILLER);
            ++(*result_rows);
        }

        copy_array(matrix[i], result_matrix[*result_rows], cols);
        ++(*result_rows);
    }
    
    return rc;
}

int digits_sum(int value)
{
    int sum = 0;
    if (value < 0)
        value *= -1;
    
    while (value > 0)
    {
        sum += value % 10;
        value /= 10;
    }

    return sum;
}

void copy_array(int *src, int *dst, int size)
{
    for (int i = 0; i < size; ++i)
        dst[i] = src[i];   
}

void fill_array(int *arr, int size, int value)
{
    for (int i = 0; i < size; ++i)
        arr[i] = value;   
}