#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"

static int calc_variance(FILE *f, float average, int amount, float *result)
{
    int rc = OK;
    float tmp = 0;
    
    if (fscanf(f, "%f", &tmp) == 1)
    {
        float variance = (tmp - average) * (tmp - average);

        while (fscanf(f, "%f", &tmp) == 1)
            variance += (tmp - average) * (tmp - average);

        variance /= amount;
        *result = variance;
    }
    else
    {
        rc = ERR_IO;
    }

    return rc;
}

int correct_3sigma_rule(FILE *f, int *result)
{
    int rc = OK;
    int amount = 0;
    float sum = 0;
    float tmp = 0, min = 0, max = 0;
    

    if (fscanf(f, "%f", &tmp) == 1)
    {
        ++amount;
        sum += tmp;
        min = max = tmp;

        while (fscanf(f, "%f", &tmp) == 1)
        {
            // не вынес подсчет среднего, минимума, и максимума в отдельные функции, 
            // так как кажется это просто лишнее чтение файла
            ++amount;
            sum += tmp;
            if (tmp < min)
                min = tmp;
            if (tmp > max)
                max = tmp;
        }

        float average = sum / amount;
        float variance = 0;
        rc = calc_variance(f, average, amount, &variance);
        if (rc == OK)
        {
            float sigma = sqrtf(variance);
            *result = average - 3 * sigma < min && average + 3 * sigma > max;
        }
    }
    else
    {
        rc = ERR_IO;
    }

    return rc;
}