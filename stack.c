#include <stdlib.h>

#include "stack.h"

struct stack {
    int size;
    int idx;
    struct ast **member;
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