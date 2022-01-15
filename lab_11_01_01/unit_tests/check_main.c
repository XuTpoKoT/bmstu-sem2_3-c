#include <stdlib.h>

#include "check_my_snprintf.h"

int main(void)
{
    int failed = 0;
    Suite *s[] = { my_snprintf_suite() };
    SRunner *runner;

    for (size_t i = 0; i < sizeof(s) / sizeof(s[0]); i++)
    {
        runner = srunner_create(s[i]);
        srunner_run_all(runner, CK_VERBOSE);
        failed += srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

