#include <stdlib.h>

#include "parser.h"
#include "stack.h"
#include "parse_context.h"
#include "parseaction.h"

struct ast *clean_operator_stack(struct parse_context *context)
{
    struct ast *node;
    struct ast *last = NULL;
    while((node = stack_pop(context->opstack)) != NULL) {
        ast_attach_right(node, stack_pop(context->expstack));
        ast_attach_left(node, stack_pop(context->expstack));
        stack_push(context->expstack, node);
        last = node;
    }
    if (NULL == last) {
        last = stack_peek(context->expstack);
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
        action = get_infix_action(node);
        action(node, context);
    }

    last = clean_operator_stack(context);

    parse_context_release(context);

    return last;
}

struct ast* parse_postfix(const char *source)
{
    struct ast *node;
    struct ast *last;
    struct parse_context *context = parse_context_create();
    parseAction *action;

    for(int i=0; source[i]; ++i) {
        node = ast_create(source[i]);
        action = get_postfix_action(node);
        action(node, context);
    }

    last = clean_operator_stack(context);
    parse_context_release(context);
    return last;
}