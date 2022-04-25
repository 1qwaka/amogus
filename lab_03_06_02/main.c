#include <stdio.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define MAX_ROWS 10
#define MAX_COLS 10

int correct_size(int size, int max_value);

int input_size(int *rows, int *cols);

void print_matrix(int **matrix, int rows, int cols);

void transform(int **matrix, int *from_buffer, int rows, int cols);

void fill_bull_move(int **matrix, int rows, int cols);

int main(void)
{
    int exit_code = OK;

    int cols = 0, rows = 0;
    int buffer[MAX_ROWS][MAX_COLS] = { 0 }; 
    int *matrix[MAX_COLS] = { 0 };

    transform(matrix, buffer[0], MAX_ROWS, MAX_COLS);

    exit_code = input_size(&rows, &cols);

    if (exit_code == OK)
    {   
        fill_bull_move(matrix, rows, cols);
        print_matrix(matrix, rows, cols);
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

int input_size(int *rows, int *cols)
{
    int rc = OK;

    rc = scanf("%d%d", rows, cols);
    rc = rc == 2 &&
        correct_size(*rows, MAX_ROWS) &&
        correct_size(*cols, MAX_COLS) 
        ? OK : ERR_INPUT;

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

void fill_bull_move(int **matrix, int rows, int cols)
{
    int step = 1;
    int fill_value = 1;
    for (int j = cols - 1; j >= 0; --j)
    {
        step *= -1;
        for (int i = step < 0 ? rows - 1 : 0; i >= 0 && i < rows; i += step)
        {
            matrix[i][j] = fill_value++;
        }
    }
}
