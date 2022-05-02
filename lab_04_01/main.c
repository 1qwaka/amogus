#include <stdio.h>
#include <string.h>

#define OK        0
#define ERR_INPUT 1
#define ERR_DATA  2

size_t my_strcspn(const char *s, const char *reject);

char *my_strchr(const char *s, int c);

char *my_strrchr(const char *s, int c);

int compare_string(const char *str1, const char *str2);

int main(void)
{
    int exit_code = OK;
    int total_tests = 7 + 5 + 5;
    int passed_tests = 0;

    passed_tests += my_strcspn("", "12345") == strcspn("", "12345");
    passed_tests += my_strcspn("abc 3152", "12345") == strcspn("abc 3152", "12345");
    passed_tests += my_strcspn("123453462", "") == strcspn("123453462", "");
    passed_tests += my_strcspn("", "") == strcspn("", "");
    passed_tests += my_strcspn("1 2 3", " ") == strcspn("1 2 3", " ");
    passed_tests += my_strcspn("aeaeaeaef", "f") == strcspn("aeaeaeaef", "f");
    passed_tests += my_strcspn("aeaeaeae", "f") == strcspn("aeaeaeae", "f");

    passed_tests += compare_string(my_strchr("abcde", 'a'), strchr("abcde", 'a')) == 0;
    passed_tests += compare_string(my_strchr("abcde", 'b'), strchr("abcde", 'b')) == 0;
    passed_tests += compare_string(my_strchr("abcde", 'e'), strchr("abcde", 'e')) == 0;
    passed_tests += compare_string(my_strchr("abcde", '\0'), strchr("abcde", '\0')) == 0;
    passed_tests += compare_string(my_strchr("abcde", 'g'), strchr("abcde", 'g')) == 0;

    passed_tests += compare_string(my_strrchr("abcde", 'a'), strrchr("abcde", 'a')) == 0;
    passed_tests += compare_string(my_strrchr("abcde", 'b'), strrchr("abcde", 'b')) == 0;
    passed_tests += compare_string(my_strrchr("abcde", 'e'), strrchr("abcde", 'e')) == 0;
    passed_tests += compare_string(my_strrchr("abcde", '\0'), strrchr("abcde", '\0')) == 0;
    passed_tests += compare_string(my_strrchr("abcde", 'g'), strrchr("abcde", 'g')) == 0;
    

    int failed_tests = total_tests - passed_tests;
    printf("%d", failed_tests);
    return exit_code;
}

int compare_string(const char *str1, const char*str2)
{
    int result = 0;
    if (str1 == NULL && str2 == NULL)
        result = OK;
    else if (str1 == NULL || str2 == NULL)
        result = ERR_DATA;
    else
        result = strcmp(str1, str2);
    
    return result;
}

size_t my_strcspn(const char *s, const char *reject)
{
    size_t len = 0;
    int found = 0;
    while (*s && !found)
    {
        for (const char *rej = reject; *rej && !found; ++rej)
            found = *s == *rej;
        ++s;
        len += !found;
    }
    
    return len;
}

char *my_strchr(const char *s, int c)
{
    char *return_s = NULL;
    int found = 0;
    while (*s && !found)
        found = *(s++) == c;

    if (!found)
        found = *(s++) == c;

    if (found)
        return_s = (char *)(s - 1);
    
    return return_s;    
}

char *my_strrchr(const char *s, int c)
{
    char *return_s = NULL;
    const char *end_s = s + strlen(s);
    int found = 0;
    
    while (end_s >= s && !found)
        found = *(end_s--) == c;

    if (found)
        return_s = (char *)(end_s + 1);
    
    return return_s;   
}