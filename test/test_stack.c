#include <check.h>

#include "../stack.h"
#include "../ast.h"

#define STACK_SIZE 5

START_TEST(stackCreate_returnsInitializedStack)
{
    struct stack *st;

    st = stack_create(STACK_SIZE);
    ck_assert_ptr_ne(st, NULL);

    stack_release(st);
}
END_TEST

START_TEST(stackPush_withAstNode_stackPopReturnsNode)
{
    struct stack *st;
    struct ast *node;
    struct ast *actual;

    st = stack_create(STACK_SIZE);
    node = ast_create('G');
    stack_push(st, node);
    actual = stack_pop(st);

    ck_assert_ptr_eq(actual, node);

    stack_release(st);
    ast_release(node);
}
END_TEST



TCase *tcase_stack(void)
{
    TCase *tc;

    tc = tcase_create("constructor-destructor");
    tcase_add_test(tc, stackCreate_returnsInitializedStack);
    tcase_add_test(tc, stackPush_withAstNode_stackPopReturnsNode);

    return tc;
}

Suite *suite_stack(void)
{
    Suite *s;

    s = suite_create("stack");
    suite_add_tcase(s, tcase_stack());

    return s;
}

