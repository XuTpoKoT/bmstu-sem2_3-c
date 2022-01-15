#include <stdlib.h>
#include "check_arr.h"

int main(void)
{
    int failed = 0;
    Suite *s[] = { mysort_suite(), key_suite() };
    SRunner *runner;

    for (size_t i = 0; i < 2; i++)
    {
        runner = srunner_create(s[i]);
        srunner_run_all(runner, CK_VERBOSE);
        failed = srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
