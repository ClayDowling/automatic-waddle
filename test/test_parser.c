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

START_TEST(parseInfix_aPlusBMinusC_returnsFiveNodesWithPlusAsParent)
{
    struct ast *tree;

    tree = parse_infix("a+b-c");

    ck_assert_int_eq(tree->symbol, '+');
    ck_assert_int_eq(tree->left->symbol, 'a');
    ck_assert_int_eq(tree->right->symbol, '-');
    ck_assert_int_eq(tree->right->left->symbol, 'b');
    ck_assert_int_eq(tree->right->right->symbol, 'c');

    ast_release(tree);
}
END_TEST

START_TEST(parseInfix_aPlusBTimesC_returnsThreeNodesWithBCChildOfPlus)
{
    struct ast *tree;
    struct ast *plus;
    struct ast *times;
    struct ast *a;
    struct ast *b;
    struct ast *c;

    tree = parse_infix("a*b+c");

    plus = tree;
    times = plus->left;
    b = times->right;
    a = times->left;
    c = plus->right;

    ck_assert_int_eq(plus->symbol, '+');
    ck_assert_int_eq(a->symbol, 'a');
    ck_assert_int_eq(times->symbol, '*');
    ck_assert_int_eq(b->symbol, 'b');
    ck_assert_int_eq(c->symbol, 'c');

    ast_release(tree);
}
END_TEST

TCase *tcase_parse_infix(void) {
    TCase *tc;

    tc = tcase_create("parse-infix");
    tcase_add_test(tc, parseInfix_aPlusB_returnsThreeNodesWithPlusAsParent);
    tcase_add_test(tc, parseInfix_aPlusBMinusC_returnsFiveNodesWithPlusAsParent);
    tcase_add_test(tc, parseInfix_aPlusBTimesC_returnsThreeNodesWithBCChildOfPlus);
    return tc;
}

Suite *suite_parser(void) {
    Suite *s;

    s = suite_create("parser");
    suite_add_tcase(s, tcase_parse_infix());

    return s;
}

