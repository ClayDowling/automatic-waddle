#include <stdlib.h>
#include "ast.h"

struct ast* ast_create(char symb)
{
	struct ast *node;

	node = (struct ast*)calloc(1, sizeof(struct ast));
	node->symbol = symb;
	return node;
}
