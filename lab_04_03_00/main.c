#include <stdio.h>
#include <string.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define CHAR_ARR_SIZE 256
#define WORD_ARR_SIZE CHAR_ARR_SIZE / WORD_MAX_SIZE
#define WORD_MAX_SIZE 16

#define WHITESPACES " \t\n"
#define DELIMETER_STR " "

void split_words(char *chars, char **words, int *words_size);

int create_string(char **words, int words_size, char *result_str);

void print_result(char *result_str);

void transform_string(char *str);

void put_string(char *dst, int idx, char *src);

void delete_char(char *str, int idx);

int main(void)
{
    int exit_code = OK;
    
    char chars[CHAR_ARR_SIZE] = { 0 };
    char *words[WORD_ARR_SIZE] = { 0 };
    int words_size = 0;
    char result_str[CHAR_ARR_SIZE] = { 0 };

    fgets(chars, sizeof(chars), stdin);

    split_words(chars, (char **)words, &words_size);

    exit_code = create_string(words, words_size, result_str);

    if (exit_code == OK)
    {
        print_result(result_str);
    }
    else
    {
        exit_code = ERR_DATA;
    }

    return exit_code;
}

void split_words(char *chars, char **words, int *words_size)
{
    *words_size = 0;
    words[0] = strtok(chars, WHITESPACES);

    if (words[0] != NULL)
    {
        *words_size = 1;
        int i = 1;
        while ( (words[i] = strtok(NULL, WHITESPACES)) != NULL )
            ++i;
        *words_size = i;        
    }
}

void print_result(char *result_str)
{
    printf("Result: %s\n", result_str);
}

int create_string(char **words, int words_size, char *result_str)
{
    int rc = OK;
    if (words_size > 1)
    {
        char *last_word = words[words_size - 1];
        words_size -= 1;

        int i = 0;
        while (words_size > 0)
        {
            if (strcmp(words[words_size - 1], last_word) != 0)
            {
                transform_string(words[words_size - 1]);
                put_string(result_str, i, words[words_size - 1]);
                i += strlen(words[words_size - 1]);
                if (words_size > 1)
                {
                    put_string(result_str, i, DELIMETER_STR);
                    i += strlen(DELIMETER_STR);
                }       
                else
                {
                    result_str[i] = '\0';
                }
            }
            --words_size;
        }

        if (i == 0)
            rc = ERR_DATA;

    }
    else
    {
        rc = ERR_DATA;
    }
    
    return rc;
}

void transform_string(char *str)
{
    char first = *(str++);
    if (first)
    {
        while (*str)
           if (*str == first)
               delete_char(str, 0);
           else
               ++str;
    }
}

void delete_char(char *str, int idx)
{
    memmove(str + idx, str + idx + 1, strlen(str + idx));
}

void put_string(char *dst, int idx, char *src)
{
    int len = strlen(src);
    char remember = dst[idx + len];
    strcpy(dst + idx, src);
    dst[idx + len] = remember;
}