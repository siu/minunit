#include <malloc.h>
#include <string.h>

static int minunit_run = 0;
static int minunit_assert = 0;
static int minunit_fail = 0;

#define MINUNIT_MESSAGE_LEN 1024
static char minunit_last_message[MINUNIT_MESSAGE_LEN];

static void (*minunit_setup)(void) = NULL;
static void (*minunit_teardown)(void) = NULL;

#define MU_TEST(method_name) static int method_name()
#define MU_TEST_SUITE(suite_name) static void suite_name()

#define MU_SUITE_CONFIGURE(setup_fun, teardown_fun) \
	minunit_setup = setup_fun; \
	minunit_teardown = teardown_fun;

#define MU_ASSERT(test, message) do {\
		minunit_assert++;\
		if (!(test)) {\
			minunit_fail++;\
			printf("F");\
			snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, message);\
			return 1;\
		} else {\
			printf(".");\
		}\
	} while (0)

#define MU_RUN_TEST(test) do {\
		if (minunit_setup) (*minunit_setup)();\
		int fail = test();\
		minunit_run++;\
		if (fail) {\
			printf("\n%s\n", minunit_last_message);\
		}\
		fflush(stdout);\
		if (minunit_teardown) (*minunit_teardown)();\
	} while (0)

// 1 tests, 1 assertions, 0 failures, 0 errors
#define MU_REPORT() printf("\n\n%d tests, %d assertions, %d failures\n", minunit_run, minunit_assert, minunit_fail)
