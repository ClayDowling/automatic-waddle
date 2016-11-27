#include <check.h>

#include "../parse_context.h"

START_TEST(parseContextCreate_returnsContextWithInitializedStacks)
{
    struct parse_context *context;

    context = parse_context_create();

    ck_assert_ptr_ne(context, NULL);
    ck_assert_ptr_ne(context->expstack, NULL);
    ck_assert_ptr_ne(context->opstack, NULL);

    parse_context_release(context);
}
END_TEST

START_TEST(parseContextRelease_givenNullContext_willNotSegfault)
{
    parse_context_release(NULL);
}
END_TEST

TCase *tcase_parsecontext(void)
{
    TCase *tc;

    tc = tcase_create("constructor-destructor");
    tcase_add_test(tc, parseContextCreate_returnsContextWithInitializedStacks);
    tcase_add_test(tc, parseContextRelease_givenNullContext_willNotSegfault);
    return tc;
}

Suite *suite_parsecontext(void)
{
    Suite *s;

    s = suite_create("parser-context");
    suite_add_tcase(s, tcase_parsecontext());

    return s;
}
