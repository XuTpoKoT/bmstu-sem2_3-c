#include <stdlib.h>

#include "check_film.h"
#include "check_films.h"

int main(void)
{
    int failed = 0;
    Suite *s[] = { copy_suite(), insert_sorted_suite() };
    SRunner *runner;

    for (size_t i = 0; i < 2; i++)
    {
        runner = srunner_create(s[i]);
        srunner_run_all(runner, CK_VERBOSE);
        failed += srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
