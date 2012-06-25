#include <malloc.h>
#include <string.h>

static int minunit_run = 0;
static int minunit_assert = 0;
static int minunit_fail = 0;

void (*mu_setup)(void) = NULL;
void (*mu_teardown)(void) = NULL;

#define MU_TEST(method_name) static char * method_name()
#define MU_TEST_SUITE(suite_name) void suite_name()

#define MU_SUITE_CONFIGURE(setup_fun, teardown_fun) \
	mu_setup = setup_fun; \
	mu_teardown = teardown_fun;

#define mu_assert(test, message) do {\
		minunit_assert++;\
		if (!(test)) {\
			minunit_fail++;\
			printf("F");\
			char *m = (char *) malloc(strlen(message) + 30);\
			sprintf(m, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, message);\
			return m;\
		} else {\
			printf(".");\
		}\
	} while (0)

#define mu_run_test(test) do {\
		if (mu_setup) (*mu_setup)();\
		char *message = test();\
		minunit_run++;\
		if (message) {\
			printf("\n%s\n", message);\
		}\
		fflush(stdout);\
		if (mu_teardown) (*mu_teardown)();\
	} while (0)

// 1 tests, 1 assertions, 0 failures, 0 errors
#define mu_report() printf("\n\n%d tests, %d assertions, %d failures\n", minunit_run, minunit_assert, minunit_fail)
