#include <check.h>
#include <stdlib.h>
#include "../buffer.h"

#define BUFFER_SIZE 10

START_TEST(bufferCreate_returnsInitializedBuffer)
{
    struct buffer *buf;

    buf = buffer_create(BUFFER_SIZE);

    ck_assert_ptr_ne(buf, NULL);
    buffer_release(buf);
}
END_TEST

START_TEST(bufferAppend_calledWithA_willReturnAString)
{
    struct buffer *buf;
    char *actual;

    buf = buffer_create(BUFFER_SIZE);

    buffer_append(buf, 'A');
    buffer_append(buf, 'B');
    actual = buffer_as_string(buf);
    ck_assert_str_eq(actual, "AB");

    free(actual);
    buffer_release(buf);
}
END_TEST

START_TEST(bufferAppend_givenBufferSizePlusOneAppends_returnsStringOfBufferSize)
{
    struct buffer *buf;
    char *actual;

    buf = buffer_create(BUFFER_SIZE);

    for(int i=0; i <= BUFFER_SIZE; ++i) {
        buffer_append(buf, 'X');
    }

    actual = buffer_as_string(buf);

    ck_assert_int_eq(strlen(actual), BUFFER_SIZE);

    free(actual);
    buffer_release(buf);
}
END_TEST

TCase *tcase_buffer(void)
{
    TCase *tc;

    tc = tcase_create("string-operations");
    tcase_add_test(tc, bufferCreate_returnsInitializedBuffer);
    tcase_add_test(tc, bufferAppend_calledWithA_willReturnAString);
    tcase_add_test(tc, bufferAppend_givenBufferSizePlusOneAppends_returnsStringOfBufferSize);

    return tc;
}

Suite *suite_buffer(void)
{
    Suite *s;

    s = suite_create("string-buffer");
    suite_add_tcase(s, tcase_buffer());

    return s;
}
