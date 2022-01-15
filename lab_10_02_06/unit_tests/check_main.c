#include <stdlib.h>

#include "check_matr.h"
#include "check_sparse_matr.h"

int main(void)
{
    int failed = 0;
    Suite *s[] = { sum_suite(), mul_suite(), pow_suite(), det_suite(), smatr_sum_suite(), smatr_mul_suite() };
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
