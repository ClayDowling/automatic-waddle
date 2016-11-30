#include <stdio.h>
#include <stdlib.h>
#include <check.h>

Suite *suite_ast(void);
Suite *suite_stack(void);
Suite *suite_traverse(void);
Suite *suite_parser(void);
Suite *suite_parsecontext(void);
Suite *suite_integration(void);
Suite *suite_buffer(void);

int main(int argc, char **argv)
{
	Suite *s;
	SRunner *runner;
	int number_fails;
    int forkme = 1;

    if (argc > 1 && strcmp(argv[1], "--nofork") == 0) {
        forkme = 0;
    }

	s = suite_ast();
	runner = srunner_create(s);
	srunner_add_suite(runner, suite_stack());
    srunner_add_suite(runner, suite_traverse());
    srunner_add_suite(runner, suite_parser());
	srunner_add_suite(runner, suite_parsecontext());
    srunner_add_suite(runner, suite_integration());
	srunner_add_suite(runner, suite_buffer());

    if (0 == forkme) {
        srunner_set_fork_status(runner, CK_NOFORK);
    }
	srunner_run_all(runner, CK_NORMAL);
	number_fails = srunner_ntests_failed(runner);

	srunner_free(runner);

	return number_fails;
}
