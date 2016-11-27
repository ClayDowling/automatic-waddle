
#ifndef POSTINFIX_PARSE_CONTEXT_H
#define POSTINFIX_PARSE_CONTEXT_H

struct parse_context {
    struct stack *opstack; /** Operator stack */
    struct stack *expstack; /** Expression stack */
};

/**
 * Initialize a new parse_context, including setting up the stacks.
 * @return Initialized parse_context
 */
struct parse_context *parse_context_create();

/**
 * Release the resources of the parse context
 * @param ctx Parse Context to release
 */
void parse_context_release(struct parse_context *ctx);

#endif //POSTINFIX_PARSE_CONTEXT_H
