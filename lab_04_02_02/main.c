#include <stdio.h>
#include <string.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

#define CHAR_ARR_SIZE 1024
#define WORD_ARR_SIZE 64
#define WORD_MAX_SIZE 64

#define YES 1
#define NO 0
#define NO_PRINT -1

#define YES_STRING "yes"
#define NO_STRING "no"

#define WHITESPACES " \t\n"

int contains_word(char **words_array, int size, char *word);

int contains_char(char *word, char c);

void split_words(char *chars, char **words, int *words_size);

int process_words(char **question_words, int question_size,
                  char **answer_words, int answer_size,
                  int *result_arr);

void print_result(char **question_words, int *result_arr, int size);

void delete_repeat(char **questions_word, int size);

int main(void)
{
    int exit_code = OK;
    
    char question_chars[CHAR_ARR_SIZE] = { 0 };
    char answer_chars[CHAR_ARR_SIZE] = { 0 };
    char *question_words[WORD_ARR_SIZE] = { 0 };
    char *answer_words[WORD_ARR_SIZE] = { 0 };
    int question_size = 0;
    int answer_size = 0;
    int result_arr[WORD_ARR_SIZE] = { 0 };

    fgets(question_chars, sizeof(question_chars), stdin);
    fgets(answer_chars, sizeof(answer_chars), stdin);

    split_words(question_chars, (char **)question_words, &question_size);
    split_words(answer_chars, (char **)answer_words, &answer_size);

    delete_repeat(question_words, question_size);
    exit_code = process_words(question_words, question_size, answer_words, answer_size, result_arr);

    if (exit_code == OK)
    {
        print_result(question_words, result_arr, question_size);
    }
    else
    {
        exit_code = ERR_DATA;
    }

    return exit_code;
}

void split_words(char *chars, char **words, int *words_size)
{
    int i = 0;
    *words_size = 0;
    int should_exit = 0;
    while (!should_exit)
    {
        while (contains_char(WHITESPACES, chars[i]))
            ++i;
        
        should_exit = !chars[i];
        if (chars[i])
        {
            words[(*words_size)++] = chars + i;
            while (chars[i] && !contains_char(WHITESPACES, chars[i]))
                ++i;
            
            should_exit = !chars[i];
            chars[i++] = '\0';
        }
    }
}

int contains_word(char **words_array, int size, char *word)
{
    int contains = 0;
    for (int i = 0; i < size && !contains; ++i)
        if (words_array[i] != NULL)
            contains = strcmp(word, words_array[i]) == 0;

    return contains;
}

int process_words(char **question_words, int question_size,
                  char **answer_words, int answer_size,
                  int *result_arr)
{
    for (int i = 0; i < question_size; ++i)
        if (question_words[i] != NULL)
        {
            result_arr[i] = NO;
            for (int j = 0; j < answer_size && result_arr[i] == NO; ++j)
            {
                result_arr[i] = strcmp(question_words[i], answer_words[j]) == 0 ? YES : NO;
            }
        }
        else
        {
            result_arr[i] = NO_PRINT;
        }
    int rc = question_size == 0 ? ERR_DATA : OK;
    return rc;
}

void print_result(char **question_words, int *result_arr, int size)
{
    for (int i = 0; i < size; ++i)
        if (result_arr[i] != NO_PRINT)
            printf("%s %s\n", question_words[i], result_arr[i] == YES ? YES_STRING : NO_STRING);    
}

void delete_repeat(char **questions_word, int size)
{
    for (int i = 1; i < size; ++i)
        if (contains_word(questions_word, i, questions_word[i]))
            questions_word[i] = NULL;
}

int contains_char(char *word, char c)
{
    int contains = 0;
    while (*word && !contains)
        contains = *(word++) == c;
    return contains;
}