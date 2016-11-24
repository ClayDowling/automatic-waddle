#ifndef POSTINFIX_STACK_H
#define POSTINFIX_STACK_H

#include "ast.h"

struct stack;

struct stack *stack_create(int size);
void stack_release(struct stack* s);

void stack_push(struct stack *s, struct ast *node);
struct ast* stack_pop(struct stack *s);

#endif //POSTINFIX_STACK_H
