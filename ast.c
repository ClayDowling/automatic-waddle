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
	free(top);
}

void ast_attach_left(struct ast *parent, struct ast *child)
{
	parent->left = child;
	child->parent = parent;
}
