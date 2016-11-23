#include <stdlib.h>
#include "ast.h"

struct ast* ast_create(char symb)
{
	struct ast *node;

	node = (struct ast*)malloc(sizeof(struct ast));

	return node;
}
