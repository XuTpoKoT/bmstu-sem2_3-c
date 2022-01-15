#include <stdio.h>
#include <string.h>

#include "my_string.h"

int main(void)
{
    setbuf(stdout, NULL);
    int correct = 0, count_tests = 0;
    
    {
        char s1[] = "asdf";
        char s2[] = "rtd";
        count_tests++;
        if (strpbrk(s1, s2) == my_strpbrk(s1, s2))
            correct++;
        char s3[] = "bb1rrrp";
        char s4[] = "mp9";
        count_tests++;
        if (strpbrk(s3, s4) == my_strpbrk(s3, s4))
            correct++;
        char s5[] = "Hello, world!";
        char s6[] = "zxcv";
        count_tests++;
        if (strpbrk(s5, s6) == my_strpbrk(s5, s6))
            correct++;
    }
    {
        char s1[] = "abacaba";
        char s2[] = "abad";
        count_tests++;
        if (strspn(s1, s2) == my_strspn(s1, s2))
            correct++;
        char s3[] = "3!gh";
        char s4[] = "3!$e";
        count_tests++;
        if (strspn(s3, s4) == my_strspn(s3, s4))
            correct++;
        char s5[] = "pensil";
        char s6[] = "pensil";
        count_tests++;
        if (strspn(s5, s6) == my_strspn(s5, s6))
            correct++;
    }
    {
        char s1[] = "abacaba";
        char s2[] = "abad";
        count_tests++;
        if (strcspn(s1, s2) == my_strcspn(s1, s2))
            correct++;
        char s3[] = "3!gh";
        char s4[] = "3!$e";
        count_tests++;
        if (strcspn(s3, s4) == my_strcspn(s3, s4))
            correct++;
        char s5[] = "qwerty";
        char s6[] = "asdf";
        count_tests++;
        if (strcspn(s5, s6) == my_strcspn(s5, s6))
            correct++;
    }
    {
        char s1[] = "abcdabcd";
        char c = 'b';
        count_tests++;
        if (strchr(s1, c) == my_strchr(s1, c))
            correct++;
        char s2[] = "abcdabcd";
        c = '\0';
        count_tests++;
        if (strchr(s2, c) == my_strchr(s2, c))
            correct++;
        char s3[] = "abcd123";
        c = 'x';
        count_tests++;
        if (strchr(s3, c) == my_strchr(s3, c))
            correct++;
    }
    {
        char s1[] = "abcdabcd";
        char c = 'b';
        count_tests++;
        if (strrchr(s1, c) == my_strrchr(s1, c))
            correct++;
        char s2[] = "abcdabcd";
        c = '\0';
        count_tests++;
        if (strrchr(s2, c) == my_strrchr(s2, c))
            correct++;
        char s3[] = "abcd123";
        c = 'x';
        count_tests++;
        if (strrchr(s3, c) == my_strrchr(s3, c))
            correct++;
    }

    
    printf("Correct tests: %d of %d.\n", correct, count_tests);

    return EXIT_SUCCESS;
}
