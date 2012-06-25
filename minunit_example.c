#include <stdio.h>
#include "minunit.h"

static int foo = 0;
static int bar = 0;

void test_setup() {
	foo = 7;
	bar = 4;
}

void test_teardown() {
	// Nothing
}

MU_TEST(test_foo) {
	MU_ASSERT(foo == 7, "foo should be 7");
	return 0;
}

MU_TEST(test_bar) {
	MU_ASSERT(bar == 4, "bar should be 4");
	bar++;
	MU_ASSERT(bar == 5, "bar should be 5");
	return 0;
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_foo);
	MU_RUN_TEST(test_bar);
}

int main(int argc, char *argv[]) {
	test_suite();
	MU_REPORT();
	return 0;
}

