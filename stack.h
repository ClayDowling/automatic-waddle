#ifndef POSTINFIX_STACK_H
#define POSTINFIX_STACK_H

struct stack;

struct stack *stack_create(int size);
void stack_release(struct stack* s);

#endif //POSTINFIX_STACK_H
