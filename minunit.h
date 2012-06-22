int minunit_run = 0;
int minunit_assert = 0;
int minunit_fail = 0;

#define MU_TEST(method_name) static char * method_name()
#define MU_TEST_SUITE(suite_name) int main(int argc, char **argv)

#define mu_assert(test, message) do {\
		minunit_assert++;\
		if (!(test)) {\
			minunit_fail++;\
			printf("F");\
			return "ERROR: " message;\
		} else {\
			printf(".");\
		}\
	} while (0)

#define mu_run_test(test) do {\
		char *message = test();\
		minunit_run++;\
		if (message) {\
			printf("\n%s\n", message);\
		}\
	} while (0)

// 1 tests, 1 assertions, 0 failures, 0 errors
#define mu_report() printf("\n\n%d tests, %d assertions, %d failures\n", minunit_run, minunit_assert, minunit_fail)
