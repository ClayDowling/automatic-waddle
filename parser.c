#include <stdlib.h>

#include "parser.h"
#include "stack.h"

struct ast* parse_infix(const char *source)
{
    struct ast *operation;
    struct ast *first;
    struct ast *second;

    first = ast_create(source[0]);
    operation = ast_create(source[1]);
    second = ast_create(source[2]);

    ast_attach_left(operation, first);
    ast_attach_right(operation, second);

    return operation;
}
