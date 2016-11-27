#include <stdlib.h>

#include "parser.h"
#include "stack.h"
#include "operator.h"

struct ast* parse_infix(const char *source)
{
    struct operator_t *op;
    struct stack *opstack;
    struct stack *expstack;
    struct ast *operation;
    struct ast *last;
    char x;

    opstack = stack_create(50);
    expstack = stack_create(500);

    for(int i=0; source[i]; ++i) {
        x = source[i];
        operation = ast_create(x);
        op = operator_get(x);
        if (op == &OP_VARIABLE) {
            stack_push(expstack, operation);
        } else if(op == &OP_LEFTPAREN) {
            stack_push(opstack, operation);
        } else if (op == &OP_RIGHTPAREN) {
            for(last = stack_pop(opstack); last->symbol != '('; last = stack_pop(opstack)) {
                ast_attach_right(last, stack_pop(expstack));
                ast_attach_left(last, stack_pop(expstack));
                stack_push(expstack, last);
            }
            ast_release(last);
            ast_release(operation);
        } else {
            last = stack_peek(opstack);
            if (NULL != last) {
                struct operator_t *op2;
                op2 = operator_get(last->symbol);
                while(op->precedence <= op2->precedence) {
                    op2 = stack_pop(opstack);
                    ast_attach_right(last, stack_pop(expstack));
                    ast_attach_left(last, stack_pop(expstack));
                    stack_push(expstack, last);
                }
            }
            stack_push(opstack, operation);
        }
    }

    while((operation = stack_pop(opstack)) != NULL) {
        ast_attach_right(operation, stack_pop(expstack));
        ast_attach_left(operation, stack_pop(expstack));
        stack_push(expstack, operation);
        last = operation;
    }

    stack_release(opstack);
    stack_release(expstack);

    return last;
}
