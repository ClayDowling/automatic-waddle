#include <stdlib.h>

#include "parser.h"
#include "stack.h"
#include "parse_context.h"
#include "parseaction.h"

struct ast *clean_operator_stack(struct parse_context *context)
{
    struct ast *node;
    struct ast *last;
    while((node = stack_pop(context->opstack)) != NULL) {
        ast_attach_right(node, stack_pop(context->expstack));
        ast_attach_left(node, stack_pop(context->expstack));
        stack_push(context->expstack, node);
        last = node;
    }
    return last;
}

struct ast* parse_infix(const char *source)
{
    struct ast *node;
    struct ast *last;
    struct parse_context *context;
    parseAction *action;
    char x;

    context = parse_context_create();

    for(int i=0; source[i]; ++i) {
        x = source[i];
        node = ast_create(x);
        action = get_action(node);
        action(node, context);
    }

    last = clean_operator_stack(context);

    parse_context_release(context);

    return last;
}
