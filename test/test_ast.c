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

START_TEST(astAttachLeft_onChildNode_setsParentOnChildLeftOnParent)
{
	struct ast *parent;
	struct ast *left;

	parent = ast_create('+');
	left = ast_create('A');
	ast_attach_left(parent, left);

	ck_assert_ptr_eq(parent->left, left);
	ck_assert_ptr_eq(left->parent, parent);

	ast_release(parent);
}
END_TEST

TCase *tcase_ast(void)
{
	TCase *tc;

	tc = tcase_create("constructor-destructor");
	tcase_add_test(tc, astCreate_givenA_returnsNodeWithAsymbolAndLeftRightNull);
	tcase_add_test(tc, astAttachLeft_onChildNode_setsParentOnChildLeftOnParent);

	return tc;
}

Suite *suite_ast(void)
{
	Suite *s;

	s = suite_create("abstract-syntax-tree");
	suite_add_tcase(s, tcase_ast());

	return s;
}
