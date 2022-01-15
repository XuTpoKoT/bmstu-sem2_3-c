#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    setbuf(stdout, NULL);

    int seconds;
    printf("Input number of seconds: \n");
    scanf("%d", &seconds);
    if (seconds < 0)
    {
        printf("Wrong input.\n");
        return EXIT_FAILURE;
    }

    int hours, minutes;
    hours = seconds / 3600;
    seconds -= hours * 3600;
    minutes = seconds / 60;
    seconds -= minutes * 60;

    printf("Hours - %d , minutes - %d , seconds - %d", hours, minutes, seconds);

    return EXIT_SUCCESS;
}
