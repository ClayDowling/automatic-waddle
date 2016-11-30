#include <stdlib.h>
#include <ctype.h>

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

void postfix_operation_action(struct ast *node, struct parse_context *context)
{
    ast_attach_right(node, stack_pop(context->expstack));
    ast_attach_left(node, stack_pop(context->expstack));
    stack_push(context->expstack, node);
}

void leftparen_action(struct ast *node, struct parse_context *context)
{
    stack_push(context->opstack, node);
}

void variable_action(struct ast *node, struct parse_context *context)
{
    stack_push(context->expstack, node);
}

parseAction* get_infix_action(struct ast *node)
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

parseAction* get_postfix_action(struct ast *node)
{
    if (node->operator == &OP_VARIABLE) {
        return variable_action;
    }

    return postfix_operation_action;
}

actionFactory *get_action_factory(const char *source)
{
    if (NULL == source) {
        return NULL;
    }
    if (isalpha(source[0]) && isalpha(source[1])) {
        return get_postfix_action;
    }
    return get_infix_action;
}

