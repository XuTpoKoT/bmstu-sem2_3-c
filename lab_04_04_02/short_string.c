#include <string.h>
#include <stdio.h>

#include "short_string.h"

int input(short_string_t str)
{
    char buf[MAX_STRING_LEN + 1];
    if (!fgets(buf, MAX_STRING_LEN + 1, stdin))
        return EMPTY_STRING;

    size_t len = strlen(buf);
    if (buf[len - 1] == '\n')
        buf[--len] = '\0';

    if (len == 0)
        return EMPTY_STRING;
    if (len >= MAX_STRING_LEN)
        return TOO_LONG_STRING;

    strcpy(str, buf);

    return EXIT_SUCCESS;
}


int split(short_string_t str, words_t words, size_t *restrict count_words, const char *restrict delims)
{
    *count_words = 0;
    size_t len_word = 0;

    for (size_t i = 0; str[i] != '\0'; i++)
        // буква в начале слова
        if (strchr(delims, str[i]) == NULL && ((*count_words) == 0 ||
            strchr(delims, str[i - 1]) != NULL))
        {
            (*count_words)++;
            len_word = 1;
            words[(*count_words) - 1][len_word - 1] = str[i];
        }
        // буква не в начале слова
        else if (i != 0 && strchr(delims, str[i]) == NULL)
        {
            len_word++;
            words[(*count_words) - 1][len_word - 1] = str[i];
        }
        // разделитель в конце слова
        else if (i != 0 && strchr(delims, str[i]) != NULL && strchr(delims, str[i - 1]) == NULL)
            words[(*count_words) - 1][++len_word - 1] = '\0';
        
    if (*count_words == 0)
        return EXIT_SUCCESS;

    if (words[(*count_words) - 1][len_word - 1] != '\0')
        words[(*count_words) - 1][len_word] = '\0';

    return EXIT_SUCCESS;
}
