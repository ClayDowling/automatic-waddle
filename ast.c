#include <stdlib.h>
#include "ast.h"

struct ast* ast_create(char symb)
{
	struct ast *node;

	node = (struct ast*)calloc(1, sizeof(struct ast));
	node->symbol = symb;
	return node;
}

void ast_release(struct ast* top)
{
	struct ast *left;
	struct ast *right;

	if (NULL == top) {
		return;
	}

	left = top->left;
	right = top->right;

	free(top);
	ast_release(left);
	ast_release(right);
}

void ast_attach_left(struct ast *parent, struct ast *child)
{
	parent->left = child;
	child->parent = parent;
}
