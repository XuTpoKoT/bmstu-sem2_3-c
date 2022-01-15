#include <stdlib.h>
#include "check_matrix.h"

int main(void)
{
    int failed = 0;
    Suite *s[] = { trunc_to_square_suite(), make_sym_size_suite(), mul_suite(), pow_suite() };
    SRunner *runner;

    for (size_t i = 0; i < 4; i++)
    {
        runner = srunner_create(s[i]);
        srunner_run_all(runner, CK_VERBOSE);
        failed += srunner_ntests_failed(runner);
        srunner_free(runner);
    }

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
