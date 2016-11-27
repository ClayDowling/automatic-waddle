#include <stdlib.h>

#include "parseaction.h"
#include "parse_context.h"
#include "ast.h"
#include "stack.h"
#include "operator.h"

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

parseAction* get_action(struct ast *node)
{
    if (node->operator == &OP_VARIABLE) {
        return variable_action;
    } else if(node->operator == &OP_LEFTPAREN) {
        return leftparen_action;
    } else if (node->operator == &OP_RIGHTPAREN) {
        return right_paren_action;
    } else {
        return operation_action;
    }
}
