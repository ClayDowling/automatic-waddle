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
	ck_assert_int_eq(node->visited, 0);
	ck_assert_ptr_eq(node->operator, &OP_VARIABLE);
	ast_release(node);

}
END_TEST

struct ast_operator_test {
    char symbol;
    struct operator_t *op;
} op_tests[] = {
        {'z', &OP_VARIABLE},
        {'+', &OP_PLUS},
        {'-', &OP_MINUS},
        {'*', &OP_TIMES},
        {'/', &OP_DIVIDE},
        {'^', &OP_EXPONENT},
        {'(', &OP_LEFTPAREN},
        {')', &OP_RIGHTPAREN}
};

START_TEST(astCreate_setsOperator)
{
    struct ast *node = ast_create(op_tests[_i].symbol);
    ck_assert_ptr_eq(node->operator, op_tests[_i].op);
    if (NULL != node) {
        ast_release(node);
    }
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
	ck_assert_ptr_eq(parent->parent, NULL);

	ast_release(parent);
}
END_TEST

START_TEST(astAttachRight_onChildNode_setsParentOnChildRightOnParent)
{
	struct ast *parent;
	struct ast *right;

	parent = ast_create('+');
	right = ast_create('Z');
	ast_attach_right(parent, right);

	ck_assert_ptr_eq(parent->right, right);
	ck_assert_ptr_eq(right->parent, parent);
	ck_assert_ptr_eq(parent->parent, NULL);

	ast_release(parent);
}
END_TEST

TCase *tcase_ast_operator(void)
{
    TCase *tc;

    tc = tcase_create("operators");
    tcase_add_loop_test(tc, astCreate_setsOperator, 0, sizeof(op_tests) / sizeof(struct ast_operator_test));

    return tc;
}

TCase *tcase_ast(void)
{
	TCase *tc;

	tc = tcase_create("constructor-destructor");
	tcase_add_test(tc, astCreate_givenA_returnsNodeWithAsymbolAndLeftRightNull);
	tcase_add_test(tc, astAttachLeft_onChildNode_setsParentOnChildLeftOnParent);
	tcase_add_test(tc, astAttachRight_onChildNode_setsParentOnChildRightOnParent);
	return tc;
}

Suite *suite_ast(void)
{
	Suite *s;

	s = suite_create("abstract-syntax-tree");
	suite_add_tcase(s, tcase_ast());
    suite_add_tcase(s, tcase_ast_operator());

	return s;
}
