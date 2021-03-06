#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "../ast.h"

static char buffer[4096];
static int buffer_idx;

struct ast *getThreenodeAst() {
    struct ast *a;
    struct ast *b;
    struct ast *plus;

    a = ast_create('A');
    b = ast_create('B');
    plus = ast_create('+');
    ast_attach_left(plus, a);
    ast_attach_right(plus, b);
    return plus;
}

struct ast *getDeepLeftAst() {
    struct ast *a;
    struct ast *b;
    struct ast *c;
    struct ast *plus;
    struct ast *minus;

    a = ast_create('A');
    b = ast_create('B');
    c = ast_create('C');
    plus = ast_create('+');
    minus = ast_create('-');

    ast_attach_left(minus, a);
    ast_attach_right(minus, b);
    ast_attach_left(plus, minus);
    ast_attach_right(plus, c);
    return plus;
}

struct ast *getDeepRightAst() {
    struct ast *a;
    struct ast *b;
    struct ast *c;
    struct ast *plus;
    struct ast *times;

    a = ast_create('A');
    b = ast_create('B');
    c = ast_create('C');
    plus = ast_create('+');
    times = ast_create('*');

    ast_attach_left(plus, a);
    ast_attach_right(plus, b);
    ast_attach_left(times, c);
    ast_attach_right(times, plus);
    return times;
}

static void setup()
{
    memset(buffer, 0, sizeof(buffer));
    buffer_idx = 0;
}

static void print_node(struct ast *node, void *notused)
{
    buffer[buffer_idx++] = node->symbol;
}

START_TEST(astTraversePostorder_givenThreeNodes_visitsLeftRightParent)
{
    struct ast *plus = getThreenodeAst();

    ast_traverse_postorder(plus, print_node, NULL);

    ck_assert_str_eq(buffer, "AB+");

    ast_release(plus);
}
END_TEST

START_TEST(astTraverseInorder_givenThreeNodes_visitsLeftParentRight)
{
    struct ast *plus = getThreenodeAst();
    ast_traverse_inorder(plus, print_node, NULL);
    ck_assert_str_eq(buffer, "A+B");
    ast_release(plus);
}
END_TEST

START_TEST(astTraversePostOrder_givenDeeperLeft_visitsDeepLeftFirst)
{
    struct ast *plus = getDeepLeftAst();

    ast_traverse_postorder(plus, print_node, NULL);

    ck_assert_str_eq(buffer, "AB-C+");

    ast_release(plus);
}
END_TEST

START_TEST(astTraverseInOrder_givenDeeperLeft_visitsDeepLeftFirst)
{
        struct ast *plus = getDeepLeftAst();

        ast_traverse_inorder(plus, print_node, NULL);

        ck_assert_str_eq(buffer, "A-B+C");

        ast_release(plus);
}
END_TEST

START_TEST(astTraversePostOrder_givenDeeperRight_visitsDeepLeftFirst)
{
    struct ast *plus = getDeepRightAst();

    ast_traverse_postorder(plus, print_node, NULL);

    ck_assert_str_eq(buffer, "CAB+*");

    ast_release(plus);
}
END_TEST

START_TEST(astTraverseInOrder_givenDeeperRight_visitsDeepLeftFirst)
{
        struct ast *plus = getDeepRightAst();

        ast_traverse_inorder(plus, print_node, NULL);

        ck_assert_str_eq(buffer, "C*A+B");

        ast_release(plus);
}
END_TEST

START_TEST(astInfix_givenDeeperRight_correctlyEncapsulatesOperatorPriority)
{
        struct ast *tree = getDeepRightAst();
        char *actual;

        actual = ast_infix(tree);
        ck_assert_str_eq(actual, "C*(A+B)");

        ast_release(tree);
        free(actual);
}
END_TEST

TCase *tcase_traverse(void)
{
    TCase *tc;

    tc = tcase_create("traversal");
    tcase_add_checked_fixture(tc, setup, NULL);
    tcase_add_test(tc, astTraversePostorder_givenThreeNodes_visitsLeftRightParent);
    tcase_add_test(tc, astTraverseInorder_givenThreeNodes_visitsLeftParentRight);
    tcase_add_test(tc, astTraversePostOrder_givenDeeperLeft_visitsDeepLeftFirst);
    tcase_add_test(tc, astTraverseInOrder_givenDeeperLeft_visitsDeepLeftFirst);
    tcase_add_test(tc, astTraversePostOrder_givenDeeperRight_visitsDeepLeftFirst);
    tcase_add_test(tc, astTraverseInOrder_givenDeeperRight_visitsDeepLeftFirst);
    tcase_add_test(tc, astInfix_givenDeeperRight_correctlyEncapsulatesOperatorPriority);

    return tc;
}

Suite *suite_traverse(void)
{
    Suite *s;

    s = suite_create("ast-traversal");
    suite_add_tcase(s, tcase_traverse());

    return s;
}

