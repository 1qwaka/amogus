#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define CHAR_ARR_SIZE 256
#define WORD_ARR_SIZE CHAR_ARR_SIZE / WORD_MAX_SIZE
#define WORD_MAX_SIZE 16

#define YEAR_WIDTH 4
#define DAY_WIDTH  2

#define DELIMETER " \t\n"

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
    char *day;
    char *month;
    char  *year;
} date_t;

int parse_data(char *chars, date_t *data);

void print_result(int is_valid);

void to_lower(char *str);

int parse_num(char *str, int *to);

int valid_data(date_t *data);

int valid_month(char *month);

int valid_day(char *day, char *month, int year);

int valid_year(char *year);

int get_days(char *month, int year);

int leap_year(int year);

int input_str(char *buffer, int size);

int main(void)
{
    int exit_code = OK;
    
    char chars[CHAR_ARR_SIZE + 1] = { 0 };

    date_t data = { 0 };

    exit_code = input_str(chars, sizeof(chars));
    if (exit_code == OK)
    {
        exit_code = parse_data(chars, &data);
        int is_valid = valid_data(&data);
        print_result(is_valid);
    }
    else
    {
        exit_code = ERR_INPUT;
    }

    return exit_code;
}

int input_str(char *buffer, int size)
{
    int rc = OK;
    int i = 0;
    int c = 0;
    while ((c = fgetc(stdin)) != EOF && i < size - 1)
    {
        buffer[i] = (char)c;
        ++i;
    }

    // if (buffer[size - 2] != '\0')
    //     rc = ERR_INPUT;
    if (fgetc(stdin) != EOF)
        rc = ERR_INPUT;

    return rc;
}

void print_result(int is_valid)
{
    if (is_valid)
        printf(YES_STR);
    else
        printf(NO_STR);
}

int parse_data(char *chars, date_t *data)
{
    int rc = OK;
    // data->day = data->year = -1;
    char *day_str = strtok(chars, DELIMETER);
    char *month_str = strtok(NULL, DELIMETER);
    char *year_str = strtok(NULL, DELIMETER);
    // char *additional = strtok(NULL, DELIMETER);

    // if (day_str != NULL && month_str != NULL && year_str != NULL)
    // {
    data->day = day_str;
    data->month = month_str;
    data->year = year_str;
        // if (strlen(day_str) <= 2 && strlen(year_str) <= 4)
        // {
        // rc = parse_num(day_str, &data->day) && parse_num(year_str, &data->year) ? OK : ERR_DATA;

        // }
        
    // }
    // else
    // {
    //     // data->valid = 0;
    //     rc = ERR_INPUT;
    // }



    // if (rc == OK)
    //     data->valid = 1;
    // else
    //     data->valid = 0;

    return rc;
}

void to_lower(char *str)
{
    while (str != NULL && *str)
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

int valid_data(date_t *data)
{
    to_lower(data->month);
    int valid = data->month != NULL && valid_month(data->month);

    valid = valid && valid_year(data->year) && valid_day(data->day, data->month, atoi(data->year));

    return valid;
}


int valid_day(char *day, char *month, int year)
{
    int valid = day != NULL && strlen(day) <= DAY_WIDTH;
    for (int i = 0; valid && day[i]; ++i)
        valid = isdigit(day[i]);

    valid = valid && atoi(day) <= get_days(month, year) && atoi(day) > 0;

    return valid;
}

int valid_year(char *year)
{
    int valid = year != NULL && strlen(year) == YEAR_WIDTH;
    for (int i = 0; valid && year[i]; ++i)
        valid = isdigit(year[i]);

    valid = valid && atoi(year) > 0;

    return valid;
}

// int all_digits()

int valid_month(char *month)
{
    int valid = 0;
    char *monthes[] = MONTHES;
    for (size_t i = 0; i < sizeof(monthes) / sizeof(monthes[0]) && !valid; ++i)
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