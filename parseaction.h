#ifndef POSTINFIX_PARSEACTION_H
#define POSTINFIX_PARSEACTION_H

#include "ast.h"
#include "parse_context.h"

typedef void (parseAction)(struct ast *node, struct parse_context *context);

/**
 * Get the correct action for this node
 * @param node
 * @return action function which should be executed for this node
 */
parseAction* get_action(struct ast *node);

#endif //POSTINFIX_PARSEACTION_H
