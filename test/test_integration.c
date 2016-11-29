#include <check.h>
#include <stdlib.h>

#include "../parser.h"
#include "../ast.h"

struct test_value {
    const char *infix;
    const char *rpn;
} cases[] = {{"a+b", "ab+"},
                             {"i+j", "ij+"},
                             {"c-d", "cd-"},
                             {"a+b-c", "abc-+"},
                             {"a-b+c", "ab-c+"},
                             {"a^b^c", "ab^c^"},
                             {"a*b/c", "abc/*"},
                             {"a/b*c", "ab/c*"},
                             {"(a+b)*c", "ab+c*"},
                             {"(a+b)^(c*d)", "ab+cd*^"},
                             {"((a+b)*c)/d", "ab+c*d/"},
                             {"(c*(a+b))/(d+e)", "cab+*de+/"},
                             {"l/m^n*o-p", "lmn^/o*p-"},
                             {"(v/w)^x*(y-z)", "vw/x^yz-*"}};

START_TEST(convert_infix_to_rpn)
{
    struct ast *tree;
    char *actual;

    tree = parse_infix(cases[_i].infix);
    actual = ast_postfix(tree);
    ck_assert_str_eq(actual, cases[_i].rpn);

    free(actual);
    ast_release(tree);
}
END_TEST

START_TEST(convert_infix_to_infix)
{
    struct ast *tree;
    char *actual;

    tree = parse_infix(cases[_i].infix);
    actual = ast_infix(tree);
    ck_assert_str_eq(actual, cases[_i].infix);

    free(actual);
    ast_release(tree);
}
END_TEST

START_TEST(convert_rpn_to_infix)
{
    struct ast *tree;
    char *actual;

    tree = parse_postfix(cases[_i].rpn);
    actual = ast_infix(tree);
    ck_assert_str_eq(actual, cases[_i].infix);

    free(actual);
    ast_release(tree);
}
END_TEST

TCase *tcase_infix(void)
{
    TCase *tc;
    int num_cases = sizeof(cases) / sizeof(struct test_value);
    tc = tcase_create("infix-to-rpn");

    tcase_add_loop_test(tc, convert_infix_to_rpn, 0, num_cases);
    tcase_add_loop_test(tc, convert_infix_to_infix, 0, num_cases);

    return tc;
}

TCase *tcase_postfix(void)
{
    TCase *tc;
    int num_cases = sizeof(cases) / sizeof(struct test_value);
    tc = tcase_create("rpn-to-infix");

    tcase_add_loop_test(tc, convert_rpn_to_infix, 0, num_cases);

    return tc;
}

Suite *suite_integration(void) {
    Suite *s;

    s = suite_create("infix-to-rpn");

    suite_add_tcase(s, tcase_infix());
    suite_add_tcase(s, tcase_postfix());

    return s;
}
