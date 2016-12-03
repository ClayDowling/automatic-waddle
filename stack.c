#include <stdlib.h>

#include "stack.h"

/**
 * Representation of a stack object.  Members should not be referenced outside of stack.c
 */
struct stack {
    int size; /**< maximum size of the stack */
    int idx; /**< current index into member */
    struct ast **member; /**< array holding the data in the stack */
};

struct stack *stack_create(int size)
{
    struct stack* s;
    s = (struct stack*)calloc(1, sizeof(struct stack));
    s->size = size;
    s->idx = 0;
    s->member = (struct ast**)calloc(s->size, sizeof(struct ast*));
    return s;
}
void stack_release(struct stack *s)
{
    if (NULL != s) {
        free(s->member);
        free(s);
    }
}

void stack_push(struct stack *s, struct ast *node)
{
    if (s->idx < s->size) {
        s->member[s->idx++] = node;
    }
}

struct ast* stack_pop(struct stack *s)
{
    if (s->idx == 0) {
        return NULL;
    }
    return s->member[--s->idx];
}

struct ast* stack_peek(struct stack *s)
{
    if (s->idx > 0) {
        return s->member[s->idx - 1];
    }
    return NULL;
}