#include <stdlib.h>

#include "stack.h"

struct stack {
    int size;
    int idx;
    struct ast **member;
};

struct stack *stack_create(int size)
{
    return (struct stack*)calloc(1, sizeof(struct stack));
}