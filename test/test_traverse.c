#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "../ast.h"

static char buffer[4096];
static int buffer_idx;

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
    struct ast *a;
    struct ast *b;
    struct ast *plus;

    a = ast_create('A');
    b = ast_create('B');
    plus = ast_create('+');
    ast_attach_left(plus, a);
    ast_attach_right(plus, b);

    ast_traverse_postorder(plus, print_node, NULL);

    ck_assert_str_eq(buffer, "AB+");

    ast_release(plus);
}
END_TEST

TCase *tcase_traverse(void)
{
    TCase *tc;

    tc = tcase_create("traversal");
    tcase_add_checked_fixture(tc, setup, NULL);
    tcase_add_test(tc, astTraversePostorder_givenThreeNodes_visitsLeftRightParent);

    return tc;
}

Suite *suite_traverse(void)
{
    Suite *s;

    s = suite_create("ast-traversal");
    suite_add_tcase(s, tcase_traverse());

    return s;
}

