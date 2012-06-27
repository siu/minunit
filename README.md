== MinUnit: Minimal unit testing framework for C

Based on evil C macros and less than 200 lines of code.

Feel free to fork, modify and improve it!

== Example

Take a look at the example minunit_example.c to see how to use this framework.

Compile with something like:

	gcc minunit_example.c -lrt -lm -o minunit_example

Don't forget to add -ltr for the timer and -lm for linking the function fabs
used in mu_assert_double_eq.

== Authors

David Siñuela Pastor <siu.4coders@gmail.com>

Note that this project is based on: http://www.jera.com/techinfo/jtns/jtn002.html
