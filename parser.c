#include <stdlib.h>

#include "parser.h"
#include "stack.h"
#include "parse_context.h"
#include "parseaction.h"

struct ast *clean_operator_stack(struct parse_context *context)
{
    struct ast *node;
    while((node = stack_pop(context->opstack)) != NULL) {
        ast_attach_right(node, stack_pop(context->expstack));
        ast_attach_left(node, stack_pop(context->expstack));
        stack_push(context->expstack, node);
    }
    return stack_pop(context->expstack);
}

struct ast* parse_from_factory(actionFactory *generator, const char *source)
{
    struct ast *node;
    struct ast *last;
    struct parse_context *context = parse_context_create();
    parseAction *action;

    for(int i=0; source[i]; ++i) {
        node = ast_create(source[i]);
        action = generator(node);
        if (action(node, context)) {
            parse_context_release(context);
            ast_release(node);
            return NULL;
        }
    }

    last = clean_operator_stack(context);
    parse_context_release(context);
    return last;
}

struct ast* parse(const char *source)
{
    actionFactory *generator = get_action_factory(source);
    return parse_from_factory(generator, source);
}

