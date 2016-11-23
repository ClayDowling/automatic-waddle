#include <check.h>
#include "../ast.h"

START_TEST(astCreate_givenA_returnsNodeWithAsymbolAndLeftRightNull)
{
	struct ast *node;

	node = ast_create('A');
	ck_assert_int_eq(node->symbol, 'A');
	ck_assert_ptr_eq(node->parent, NULL);
	ck_assert_ptr_eq(node->left, NULL);
	ck_assert_ptr_eq(node->right, NULL);
	ast_release(node);

}
END_TEST

TCase *tcase_ast(void)
{
	TCase *tc;

	tc = tcase_create("constructor-destructor");
	tcase_add_test(tc, astCreate_givenA_returnsNodeWithAsymbolAndLeftRightNull);

	return tc;
}

Suite *suite_ast(void)
{
	Suite *s;

	s = suite_create("abstract-syntax-tree");
	suite_add_tcase(s, tcase_ast());

	return s;
}
