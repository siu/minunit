#ifdef __cplusplus
	extern "C" {
#endif

#include <stdio.h>
#include <time.h>
#include <math.h>

// Maximum length of last message
#define MINUNIT_MESSAGE_LEN 1024
// Do not change
#define MINUNIT_EPSILON 1E-12

// Misc. counters
static int minunit_run = 0;
static int minunit_assert = 0;
static int minunit_fail = 0;
static int minunit_status = 0;

// Timers
typedef struct timespec timespec_t ;
static timespec_t minunit_real_timer = { 0, 0 };
static timespec_t minunit_proc_timer = { 0, 0 };

// Last message
static char minunit_last_message[MINUNIT_MESSAGE_LEN];

// Test setup and teardown function pointers
static void (*minunit_setup)(void) = NULL;
static void (*minunit_teardown)(void) = NULL;

// Definitions
#define MU_TEST(method_name) static void method_name()
#define MU_TEST_SUITE(suite_name) static void suite_name()

// Run test suite and unset setup and teardown functions
#define MU_RUN_SUITE(suite_name) do {\
	suite_name();\
	minunit_setup = NULL;\
	minunit_teardown = NULL;\
	} while(0)

// Configure setup and teardown functions
#define MU_SUITE_CONFIGURE(setup_fun, teardown_fun) do {\
	minunit_setup = setup_fun;\
	minunit_teardown = teardown_fun;\
	} while (0)

// Test runner
#define MU_RUN_TEST(test) do {\
		if (minunit_real_timer.tv_sec==0 && minunit_real_timer.tv_nsec==0) {\
			clock_gettime(CLOCK_MONOTONIC, &minunit_real_timer);\
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &minunit_proc_timer);\
		}\
		if (minunit_setup) (*minunit_setup)();\
		minunit_status = 0;\
		test();\
		minunit_run++;\
		if (minunit_status) {\
			minunit_fail++;\
			printf("F");\
			printf("\n%s\n", minunit_last_message);\
		}\
		fflush(stdout);\
		if (minunit_teardown) (*minunit_teardown)();\
	} while (0)

// Report
#define MU_REPORT() do {\
	printf("\n\n%d tests, %d assertions, %d failures\n", minunit_run, minunit_assert, minunit_fail);\
	timespec_t end_real_timer, end_proc_timer;\
	clock_gettime(CLOCK_MONOTONIC, &end_real_timer);\
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_proc_timer);\
	printf("\nFinished in %.8f seconds (real) %.8f seconds (proc)\n\n",\
		mu_timer_diff(&minunit_real_timer, &end_real_timer),\
		mu_timer_diff(&minunit_proc_timer, &end_proc_timer));\
	} while (0)

// Assertions
#define mu_check(test) do {\
		minunit_assert++;\
		if (!(test)) {\
			snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, #test);\
			minunit_status = 1;\
			return;\
		} else {\
			printf(".");\
		}\
	} while (0)

#define mu_fail(message) do {\
		minunit_assert++;\
		snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, message);\
		minunit_status = 1;\
		return;\
	} while (0)

#define mu_assert(test, message) do {\
		minunit_assert++;\
		if (!(test)) {\
			snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, message);\
			minunit_status = 1;\
			return;\
		} else {\
			printf(".");\
		}\
	} while (0)

#define mu_assert_int_eq(expected, result) do {\
		minunit_assert++;\
		int minunit_tmp_e = (expected);\
		int minunit_tmp_r = (result);\
		if (minunit_tmp_e != minunit_tmp_r) {\
			snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %d expected but was %d", __func__, __FILE__, __LINE__, minunit_tmp_e, minunit_tmp_r);\
			minunit_status = 1;\
			return;\
		} else {\
			printf(".");\
		}\
	} while (0)

#define mu_assert_double_eq(expected, result) do {\
		minunit_assert++;\
		double minunit_tmp_e = (expected);\
		double minunit_tmp_r = (result);\
		if (fabs(minunit_tmp_e-minunit_tmp_r) > MINUNIT_EPSILON) {\
			snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %g expected but was %g", __func__, __FILE__, __LINE__, minunit_tmp_e, minunit_tmp_r);\
			minunit_status = 1;\
			return;\
		} else {\
			printf(".");\
		}\
	} while (0)

// Misc. utilities
static inline double mu_timer_diff(timespec_t *start, timespec_t *end)
{
#define MINUNIT_NSECS 1e9
	return (((  end->tv_sec * MINUNIT_NSECS) +   end->tv_nsec) -
			((start->tv_sec * MINUNIT_NSECS) + start->tv_nsec)) / MINUNIT_NSECS;
}

#ifdef __cplusplus
}
#endif
