#include <stdio.h>
#include "minunit.h"

static int foo = 0;
static int bar = 0;

void test_setup() {
	foo = 7;
	bar = 4;
}

/*
void test_teardown() {
}
*/

MU_TEST(test_foo) {
	mu_assert(foo == 7, "foo should be 7");
	return 0;
}

MU_TEST(test_bar) {
	mu_assert(bar == 5, "bar should be 5");
	return 0;
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, NULL);
	//MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	mu_run_test(test_foo);
	mu_run_test(test_foo);
	mu_run_test(test_foo);
	mu_run_test(test_foo);
	mu_run_test(test_foo);
	mu_run_test(test_bar);
	mu_run_test(test_foo);
	mu_run_test(test_foo);
}

int main(int argc, char *argv[]) {
	test_suite();
	mu_report();
	return 0;
}

