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

START_TEST(stachPush_withTwoNodes_stackPopReturnsBothNodes)
{
    struct stack *st;
    struct ast *a;
    struct ast *b;
    struct ast *actual;

    st = stack_create(STACK_SIZE);
    a = ast_create('A');
    b = ast_create('B');
    stack_push(st, a);
    stack_push(st, b);

    actual = stack_pop(st);
    ck_assert_ptr_eq(b, actual);

    actual = stack_pop(st);
    ck_assert_ptr_eq(a, actual);

    ast_release(a);
    ast_release(b);
    stack_release(st);
}
END_TEST

START_TEST(stackPop_ifCalledMoreThanStackPush_returnsNull)
{
    struct stack *st;
    struct ast *a;

    st = stack_create(STACK_SIZE);
    a = ast_create('A');
    stack_push(st, a);
    stack_pop(st);

    ck_assert_ptr_eq(stack_pop(st), NULL);

    stack_release(st);
    ast_release(a);
}
END_TEST

START_TEST(stackPush_ifCalledMoreThanStackSize_discardsExtraMembers)
{
    struct stack *st;
    struct ast *a;
    struct ast *b;

    st = stack_create(1);
    a = ast_create('A');
    b = ast_create('B');

    stack_push(st, a);
    stack_push(st, b);

    ck_assert_ptr_eq(stack_pop(st), a);
    ck_assert_ptr_eq(stack_pop(st), NULL);

    stack_release(st);
    ast_release(a);
    ast_release(b);
}
END_TEST

TCase *tcase_stack(void)
{
    TCase *tc;

    tc = tcase_create("constructor-destructor");
    tcase_add_test(tc, stackCreate_returnsInitializedStack);
    tcase_add_test(tc, stackPush_withAstNode_stackPopReturnsNode);
    tcase_add_test(tc, stachPush_withTwoNodes_stackPopReturnsBothNodes);
    tcase_add_test(tc, stackPop_ifCalledMoreThanStackPush_returnsNull);
    tcase_add_test(tc, stackPush_ifCalledMoreThanStackSize_discardsExtraMembers);

    return tc;
}

Suite *suite_stack(void)
{
    Suite *s;

    s = suite_create("stack");
    suite_add_tcase(s, tcase_stack());

    return s;
}

