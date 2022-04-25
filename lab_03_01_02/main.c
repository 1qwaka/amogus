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

int custom_sign(int value);

int process_matrix(int *result_arr, int **matrix, int rows, int cols);

void print_array(int *arr, int size);

int main(void)
{
    int exit_code = OK;

    int cols = 0, rows = 0;
    int buffer[MAX_ROWS][MAX_COLS] = { 0 }; 
    int *matrix[MAX_COLS] = { 0 };
    int result_array[MAX_COLS] = { 0 };

    transform(matrix, buffer[0], MAX_ROWS, MAX_COLS);
    exit_code = input_matrix(matrix, &rows, &cols);

    if (exit_code == OK)
    {
        exit_code = process_matrix(result_array, matrix, rows, cols);
        if (exit_code == OK)
        {
            print_array(result_array, cols);
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

int custom_sign(int value)
{
    return value < 0 ? -1 : (value == 0 ? 0 : 1);
}

int process_matrix(int *result_arr, int **matrix, int rows, int cols)
{
    int rc = OK;

    if (rows > 1)
    {
        for (int i = 0; i < cols; ++i)
        {
            int flag = 1;
            for (int j = 1; j < rows && flag; ++j)
            {
                flag = flag && custom_sign(matrix[j - 1][i]) * custom_sign(matrix[j][i]) < 0;
            }
            result_arr[i] = flag;
        }
    }
    else if (rows == 1)
    {
        for (int i = 0; i < cols; ++i)
            result_arr[i] = 0;
    }
    else
    {
        rc = ERR_DATA;
    }
    
    return rc;
}

void print_array(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
        printf("%d ", arr[i]);
    printf("%d", arr[size - 1]);
}
