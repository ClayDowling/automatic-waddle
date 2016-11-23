#include <check.h>

#include "../stack.h"

#define STACK_SIZE 5

START_TEST(stackCreate_returnsInitializedStack)
{
    struct stack *st;

    st = stack_create(STACK_SIZE);
    ck_assert_ptr_ne(st, NULL);

    stack_release(st);
}
END_TEST

TCase *tcase_stack(void)
{
    TCase *tc;

    tc = tcase_create("constructor-destructor");
    tcase_add_test(tc, stackCreate_returnsInitializedStack);

    return tc;
}

Suite *suite_stack(void)
{
    Suite *s;

    s = suite_create("stack");
    suite_add_tcase(s, tcase_stack());

    return s;
}

