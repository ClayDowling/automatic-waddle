#include <stdlib.h>

#include "parser.h"
#include "stack.h"
#include "operator.h"
#include "parse_context.h"

void right_paren_action(struct ast *node, struct parse_context *context)
{
    struct ast *last;
    for(last = stack_pop(context->opstack); last->symbol != '('; last = stack_pop(context->opstack)) {
        ast_attach_right(last, stack_pop(context->expstack));
        ast_attach_left(last, stack_pop(context->expstack));
        stack_push(context->expstack, last);
    }
    ast_release(last);
    ast_release(node);
}

void operation_action(struct ast *node, struct parse_context *context)
{
    struct ast *last;
    for(last = stack_peek(context->opstack);
        NULL != last && node->operator->precedence <= last->operator->precedence;
        last = stack_peek(context->opstack)) {
        stack_pop(context->opstack);
        ast_attach_right(last, stack_pop(context->expstack));
        ast_attach_left(last, stack_pop(context->expstack));
        stack_push(context->expstack, last);
    }
    stack_push(context->opstack, node);
}

void leftparen_action(struct ast *node, struct parse_context *context)
{
    stack_push(context->opstack, node);
}

void variable_action(struct ast *node, struct parse_context *context)
{
    stack_push(context->expstack, node);
}

struct ast* parse_infix(const char *source)
{
    struct ast *node;
    struct ast *last;
    struct parse_context *context;
    char x;

    context = parse_context_create();

    for(int i=0; source[i]; ++i) {
        x = source[i];
        node = ast_create(x);
        if (node->operator == &OP_VARIABLE) {
            variable_action(node, context);
        } else if(node->operator == &OP_LEFTPAREN) {
            leftparen_action(node, context);
        } else if (node->operator == &OP_RIGHTPAREN) {
            right_paren_action(node, context);
        } else {
            operation_action(node, context);
        }
    }

    while((node = stack_pop(context->opstack)) != NULL) {
        ast_attach_right(node, stack_pop(context->expstack));
        ast_attach_left(node, stack_pop(context->expstack));
        stack_push(context->expstack, node);
        last = node;
    }

    parse_context_release(context);

    return last;
}
