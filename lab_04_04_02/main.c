#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define CHAR_ARR_SIZE 256
#define WORD_ARR_SIZE CHAR_ARR_SIZE / WORD_MAX_SIZE
#define WORD_MAX_SIZE 16

#define WHITESPACES " \t\n"

#define YES_STR "YES"
#define NO_STR  "NO"

#define MONTHES { \
"january",\
"february",\
"march",\
"april",\
"may",\
"june",\
"july",\
"august",\
"september",\
"october",\
"november",\
"december" }

#define MONTHES_DAYS { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }

typedef struct 
{
    int day;
    char *month;
    int year;
} data_t;

int parse_data(char *chars, data_t *data);

void print_result(int is_valid);

void to_lower(char *str);

int parse_num(char *str, int *to);

int valid_data(data_t *data);

int valid_month(char *month);

int get_days(char *month, int year);

int leap_year(int year);

int main(void)
{
    int exit_code = OK;
    
    char chars[CHAR_ARR_SIZE] = { 0 };
    data_t data = { 0 };

    fgets(chars, sizeof(chars), stdin);

    exit_code = parse_data(chars, &data);

    if ( exit_code == OK)
    {
        int is_valid = valid_data(&data);
        print_result(is_valid);
    }
    else
    {
        exit_code = ERR_INPUT;
    }

    return exit_code;
}

void print_result(int is_valid)
{
    if (is_valid)
        printf(YES_STR);
    else
        printf(NO_STR);
}

int parse_data(char *chars, data_t *data)
{
    int rc = OK;
    data->day = data->year = -1;
    char *day_str = strtok(chars, WHITESPACES);
    char *month_str = strtok(NULL, WHITESPACES);
    char *year_str = strtok(NULL, WHITESPACES);

    if (day_str != NULL && month_str != NULL && year_str != NULL)
    {
        data->month = month_str;
        rc = parse_num(day_str, &data->day) && parse_num(year_str, &data->year) ? OK : ERR_DATA;
    }
    else
    {
        rc = ERR_INPUT;
    }

    return rc;
}

void to_lower(char *str)
{
    while (*str)
    {
        if ('A' <= *str && *str <= 'Z')
            *str += ('a' - 'A');
        ++str;
    }
}

int parse_num(char *str, int *to)
{
    char *end = NULL;
    *to = strtol(str, &end, 10);
    return *end == '\0';
}

int valid_data(data_t *data)
{
    to_lower(data->month);
    int valid = valid_month(data->month);
    valid = valid && data->day > 0 && data->day <= get_days(data->month, data->year);
    valid = valid && data->year > 0;

    return valid;
}

int valid_month(char *month)
{
    int valid = 0;
    char *monthes[] = MONTHES;
    for (int i = 0; i < (int)(sizeof(monthes) / sizeof(monthes[0])) && !valid; ++i)
        valid = strcmp(month, monthes[i]) == 0;

    return valid;    
}

int get_days(char *month, int year)
{
    int days = -1;
    char *monthes[] = MONTHES;
    int monthes_days[] = MONTHES_DAYS;
    int i = 0;
    for (; i < (int)(sizeof(monthes) / sizeof(monthes[0])) && days == -1; ++i)
        if (strcmp(month, monthes[i]) == 0)
            days = monthes_days[i];
    
    if (i == 2 && leap_year(year))
        ++days;

    return days;
}

int leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}