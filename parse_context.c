#include <stdlib.h>

#include "parse_context.h"
#include "stack.h"

struct parse_context* parse_context_create()
{
    struct parse_context *c;
    c = (struct parse_context*)calloc(1, sizeof(struct parse_context));
    c->expstack = stack_create(500);
    c->opstack = stack_create(50);
    return c;
}

void parse_context_release(struct parse_context *ctx)
{
    if (NULL != ctx) {
        stack_release(ctx->opstack);
        stack_release(ctx->expstack);
        free(ctx);
    }
}