#include <check.h>
#include <stdlib.h>

#include "../parser.h"

START_TEST(parseInfix_aPlusB_returnsThreeNodesWithPlusAsParent)
{
    struct ast *tree;

    tree = parse("a+b");

    ck_assert_int_eq(tree->symbol, '+');
    ck_assert_int_eq(tree->left->symbol, 'a');
    ck_assert_int_eq(tree->right->symbol, 'b');

    ast_release(tree);
}
END_TEST

START_TEST(parseInfix_aPlusBMinusC_returnsFiveNodesWithPlusAsParent)
{
    struct ast *tree;

    tree = parse("a+b-c");

    ck_assert_int_eq(tree->symbol, '+');
    ck_assert_int_eq(tree->left->symbol, 'a');
    ck_assert_int_eq(tree->right->symbol, '-');
    ck_assert_int_eq(tree->right->left->symbol, 'b');
    ck_assert_int_eq(tree->right->right->symbol, 'c');

    ast_release(tree);
}
END_TEST

START_TEST(parseInfix_aTimesBPlusC_returnsFiveNodesWithTimesChildOfPlus)
{
    struct ast *tree;
    struct ast *plus;
    struct ast *times;
    struct ast *a;
    struct ast *b;
    struct ast *c;

    tree = parse("a*b+c");

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

START_TEST(parseInfix_aTimesParenBPlusCParen_returnsThreeNodesWithBCChildOfTimes)
{
        struct ast *tree;
        struct ast *plus;
        struct ast *times;
        struct ast *a;
        struct ast *b;
        struct ast *c;
        char *asstring;

        tree = parse("a*(b+c)");

        asstring = ast_postfix(tree);

        ck_assert_str_eq(asstring, "abc+*");

        free(asstring);
        ast_release(tree);
}
END_TEST

START_TEST(parse_givenUnbalancedParens_returnsNull)
{
    struct ast *tree;

    tree = parse("a+b)*c");

    ck_assert_ptr_eq(tree, NULL);
}
END_TEST

START_TEST(parse_givenTwoOperandsAndTwoOperatorsForPostfix_returnsNull)
{
    struct ast *tree;

    tree = parse("ab++");

    ck_assert_ptr_eq(tree, NULL);
}
END_TEST

START_TEST(parse_givenTwoOperandsAndTwoOperatorsForInfix_returnsNull)
{
    struct ast *tree;

    tree = parse("a+b+");

    ck_assert_ptr_eq(tree, NULL);
}
END_TEST

START_TEST(parse_givenOneOperandAndOneOperatorInParens_returnsNull)
{
    struct ast *tree;

    tree = parse("(a+)*c");

    ck_assert_ptr_eq(tree, NULL);
}
END_TEST

TCase *tcase_parse_infix(void) {
    TCase *tc;

    tc = tcase_create("parse-infix");
    tcase_add_test(tc, parseInfix_aPlusB_returnsThreeNodesWithPlusAsParent);
    tcase_add_test(tc, parseInfix_aPlusBMinusC_returnsFiveNodesWithPlusAsParent);
    tcase_add_test(tc, parseInfix_aTimesBPlusC_returnsFiveNodesWithTimesChildOfPlus);
    tcase_add_test(tc, parseInfix_aTimesParenBPlusCParen_returnsThreeNodesWithBCChildOfTimes);
    tcase_add_test(tc, parse_givenUnbalancedParens_returnsNull);
    tcase_add_test(tc, parse_givenTwoOperandsAndTwoOperatorsForPostfix_returnsNull);
    tcase_add_test(tc, parse_givenTwoOperandsAndTwoOperatorsForInfix_returnsNull);
    tcase_add_test(tc, parse_givenOneOperandAndOneOperatorInParens_returnsNull);

    return tc;
}

Suite *suite_parser(void) {
    Suite *s;

    s = suite_create("parser");
    suite_add_tcase(s, tcase_parse_infix());

    return s;
}

