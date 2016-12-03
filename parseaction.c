#include <stdlib.h>
#include <ctype.h>

#include "parseaction.h"
#include "parse_context.h"
#include "ast.h"
#include "stack.h"
#include "operator.h"

int apply_operator_to_operands(struct ast *operator, struct parse_context *context)
{
    struct ast *left;
    struct ast *right;

    right = stack_pop(context->expstack);
    left = stack_pop(context->expstack);

    if (!right || !left) {
        if (right)
            ast_release(right);
        return 1;
    }

    ast_attach_right(operator, right);
    ast_attach_left(operator, left);
    stack_push(context->expstack, operator);

    return 0;
}

int right_paren_action(struct ast *node, struct parse_context *context)
{
    struct ast *last;
    struct ast *left;
    struct ast *right;

    for(last = stack_pop(context->opstack); last && last->symbol != '('; last = stack_pop(context->opstack)) {
        if (apply_operator_to_operands(last, context)) {
            ast_release(last);
            return 1;
        }
    }
    if (NULL == last) { // Did not find left paren
        return 1;
    }

    ast_release(last);
    ast_release(node);

    return 0;
}

int operation_action(struct ast *node, struct parse_context *context)
{
    struct ast *last;
    for(last = stack_peek(context->opstack);
        NULL != last && node->operator->precedence <= last->operator->precedence;
        last = stack_peek(context->opstack)) {
        stack_pop(context->opstack);

        if (apply_operator_to_operands(last, context)) {
            return 1;
        }
    }
    stack_push(context->opstack, node);

    return 0;
}

int postfix_operation_action(struct ast *node, struct parse_context *context)
{
    return apply_operator_to_operands(node, context);
}

int leftparen_action(struct ast *node, struct parse_context *context)
{
    stack_push(context->opstack, node);

    return 0;
}

int variable_action(struct ast *node, struct parse_context *context)
{
    stack_push(context->expstack, node);

    return 0;
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

