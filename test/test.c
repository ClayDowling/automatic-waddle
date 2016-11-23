#include <stdio.h>
#include <stdlib.h>
#include <check.h>

Suite *suite_ast(void);


int main(int argc, char **argv)
{
	Suite *s;
	SRunner *runner;
	int number_fails;

	s = suite_ast();
	runner = srunner_create(s);

	srunner_run_all(runner, CK_NORMAL);
	number_fails = srunner_ntests_failed(runner);

	srunner_free(runner);

	return number_fails;
}
