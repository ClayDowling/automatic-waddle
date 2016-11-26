#ifndef POSTINFIX_STACK_H
#define POSTINFIX_STACK_H

#include "ast.h"

struct stack;

/**
 * Iniialize a stack structure
 * @param size of the stack
 * @return pointer to the new stack
 */
struct stack *stack_create(int size);

/**
 * Free the stack resources.  Does not release the resources of anything
 * stored in the stack.
 * @param s stack which is being freed
 */
void stack_release(struct stack* s);

/**
 * Put a new AST node on the stack.  If the stack is already full the new
 * node will be discarded.
 * @param s stack to append to.
 * @param node to be put on the stack.
 */
void stack_push(struct stack *s, struct ast *node);

/**
 * Remove a member from the stack
 * @param s stack to pop
 * @return node found on the stack, NULL if there are no more members.
 */
struct ast* stack_pop(struct stack *s);

/**
 * Look at the top element of the stack, but leave it on the stack.
 * @param s Stack to examine
 * @return struct ast* of the top member, or NULL if the stack is empty
 */
struct ast* stack_peek(struct stack *s);

#endif //POSTINFIX_STACK_H
