#include <stdlib.h>

#include "parser.h"
#include "stack.h"
#include "operator.h"

struct ast* parse_infix(const char *source)
{
    struct stack *opstack;
    struct stack *expstack;
    struct ast *node;
    struct ast *last;
    char x;

    opstack = stack_create(50);
    expstack = stack_create(500);

    for(int i=0; source[i]; ++i) {
        x = source[i];
        node = ast_create(x);
        if (node->operator == &OP_VARIABLE) {
            stack_push(expstack, node);
        } else if(node->operator == &OP_LEFTPAREN) {
            stack_push(opstack, node);
        } else if (node->operator == &OP_RIGHTPAREN) {
            for(last = stack_pop(opstack); last->symbol != '('; last = stack_pop(opstack)) {
                ast_attach_right(last, stack_pop(expstack));
                ast_attach_left(last, stack_pop(expstack));
                stack_push(expstack, last);
            }
            ast_release(last);
            ast_release(node);
        } else {
            for(last = stack_peek(opstack);
                NULL != last && node->operator->precedence <= last->operator->precedence;
                last = stack_peek(opstack)) {
                    stack_pop(opstack);
                    ast_attach_right(last, stack_pop(expstack));
                    ast_attach_left(last, stack_pop(expstack));
                    stack_push(expstack, last);
            }
            stack_push(opstack, node);
        }
    }

    while((node = stack_pop(opstack)) != NULL) {
        ast_attach_right(node, stack_pop(expstack));
        ast_attach_left(node, stack_pop(expstack));
        stack_push(expstack, node);
        last = node;
    }

    stack_release(opstack);
    stack_release(expstack);

    return last;
}
