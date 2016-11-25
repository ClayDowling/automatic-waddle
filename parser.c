#include <stdlib.h>

#include "parser.h"
#include "stack.h"

struct operator_t {
    char symbol;
    int precedence;
};

struct operator_t OP_PLUS = {'+', 1};
struct operator_t OP_MINUS = {'-', 2};
struct operator_t OP_TIMES = {'*', 3};
struct operator_t OP_DIVIDE = {'/', 4};
struct operator_t OP_EXPONENT = {'^', 5};

struct operator_t* get_operator(char op)
{
    struct operator_t *operators[] = {
            &OP_PLUS,
            &OP_MINUS,
            &OP_TIMES,
            &OP_DIVIDE,
            &OP_EXPONENT,
            NULL
    };

    for(int i = 0; operators[i]; ++i) {
        if (operators[i]->symbol == op) {
            return operators[i];
        }
    }
    return NULL;
}

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
        op = get_operator(x);
        if (op == NULL) {
            stack_push(expstack, operation);
        } else {
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
