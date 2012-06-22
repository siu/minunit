#include <stdio.h>
#include "minunit.h"

int foo = 7;
int bar = 4;

MU_TEST(test_foo) {
    mu_assert(foo == 7, "foo should be 7");
    return 0;
}

MU_TEST(test_bar) {
    mu_assert(bar == 5, "bar should be 5");
    return 0;
}

MU_TEST_SUITE(all_tests) {
    mu_run_test(test_foo);
    mu_run_test(test_foo);
    mu_run_test(test_foo);
    mu_run_test(test_foo);
    mu_run_test(test_foo);
    mu_run_test(test_bar);
    mu_run_test(test_foo);
    mu_run_test(test_foo);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
	mu_report();

    return result != 0;
}
