#include "check_.h"

int main(void)
{
    Suite *s[] = { copy_suite() };
    SRunner *runner;

    for (size_t i = 0; i < 1; i++)
    {
        runner = srunner_create(s[i]);
        srunner_run_all(runner, CK_VERBOSE);
        srunner_free(runner);
    }

    return 0;
}
