#include "short_string.h"

#include <stdio.h>
#include <string.h>

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
            if (++len_word > MAX_WORD_LEN - 1)
                return TOO_LONG_WORD;
            words[(*count_words) - 1][len_word - 1] = str[i];
        }
        // разделитель в конце слова
        else if (i != 0 && strchr(delims, str[i]) != NULL && strchr(delims, str[i - 1]) == NULL)
            words[(*count_words) - 1][++len_word - 1] = '\0';
        
    if (*count_words == 0)
        return NO_WORDS;

    if (words[(*count_words) - 1][len_word - 1] != '\0')
        words[(*count_words) - 1][len_word] = '\0';

    return EXIT_SUCCESS;
}

void del_chars_equal_first(word_t word)
{
    if (strlen(word) == 0)
        return;
    word_t buf;
    size_t buf_len = 0;
    strcpy(buf, "");
    buf[buf_len++] = word[0];
    for (size_t i = 1; word[i]; i++)
        if (word[i] != word[0])
            buf[buf_len++] = word[i];
    buf[buf_len] = '\0';
    strcpy(word, buf);
}

int joinr(words_t words, size_t count_words, short_string_t str)
{
    if (count_words <= 1)
        return EMPTY_STRING;
    
    strcpy(str, "");
    size_t len = 0;
    
    for (size_t i = count_words - 2; i > 0; i--)
        if (strcmp(words[i], words[count_words - 1]) != 0)
        {
            size_t len_word = strlen(words[i]);
            if (len > MAX_STRING_LEN - len_word - 1)
                return STRING_OVERFLOW;
            word_t word;
            strcpy(word, words[i]);
            del_chars_equal_first(word);
            strcat(str, word);
            strcat(str, " ");
            len += len_word + 1;
        }
    if (strcmp(words[0], words[count_words - 1]) != 0)
    {
        if (len > MAX_STRING_LEN - strlen(words[0]) - 1)
            return STRING_OVERFLOW;
        word_t word;
        strcpy(word, words[0]);
        del_chars_equal_first(word);
        strcat(str, word);
    }
    
    if (strcmp(str, "") == 0)
        return EMPTY_STRING;
    return EXIT_SUCCESS;
}
