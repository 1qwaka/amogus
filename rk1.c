// Степаненко Андрей ИУ7-25Б
// РК1, Вариант 2
#include <stdio.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define MAX_ARR_SIZE 10

int input_array(int arr[], int *size);

int group_array(int arr[], int size);

void print_array(int arr[], int size);

int main(void)
{
    int exit_code = 0;

    int arr[MAX_ARR_SIZE] = { 0 };
    int size = 0;
    int rc = 0;

    rc = input_array(arr, &size);
    if (rc == OK)
    {
        rc = group_array(arr, size);

        if (rc == OK)
            print_array(arr, size);
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
    int rc = 0;
    rc = scanf("%d", size);

    if (rc == 1 && *size > 0 && *size < MAX_ARR_SIZE)
    {
        for(int i = 0; (i < *size) && rc == 1; ++i)
        {
            rc = scanf("%d", arr + i);
        }
        if (rc == 1)
            rc = OK;
        else
            rc = ERR_INPUT;
    }
    else
    {
        rc = ERR_INPUT;
    }

    return rc;
}

int group_array(int arr[], int size)
{
    int tmp = 0;

    // перемещаем четные в начало
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if ((arr[j + 1] % 2 == 0) && (arr[j] % 2 != 0))
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }

    // перемещаем нули в конец
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if ((arr[j + 1] != 0) && (arr[j] == 0))
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }

    // в данной задаче любые корректно введенные данные считаю валидными,
    // то есть их можно сгруппировать каким либо образом
    return OK;
}

void print_array(int arr[], int size)
{
    // нет проверки на массив совсем без элементов
    printf("%d", arr[0]);
    for(int i = 1; i < size; ++i)
    {
        printf(" %d", arr[i]);
    }
}













