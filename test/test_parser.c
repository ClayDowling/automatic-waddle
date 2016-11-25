#include <check.h>

#include "../parser.h"

START_TEST(parseInfix_aPlusB_returnsThreeNodesWithPlusAsParent)
{
    struct ast *tree;

    tree = parse_infix("a+b");

    ck_assert_int_eq(tree->symbol, '+');
    ck_assert_int_eq(tree->left->symbol, 'a');
    ck_assert_int_eq(tree->right->symbol, 'b');

    ast_release(tree);
}
END_TEST

TCase *tcase_parse_infix(void)
{
    TCase *tc;

    tc = tcase_create("parse-infix");
    tcase_add_test(tc, parseInfix_aPlusB_returnsThreeNodesWithPlusAsParent);

    return tc;
}

Suite *suite_parser(void)
{
    Suite *s;

    s = suite_create("parser");
    suite_add_tcase(s, tcase_parse_infix());

    return s;
}

