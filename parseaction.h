#ifndef POSTINFIX_PARSEACTION_H
#define POSTINFIX_PARSEACTION_H

#include "ast.h"
#include "parse_context.h"

typedef void (parseAction)(struct ast *node, struct parse_context *context);

typedef parseAction* (actionFactory)(struct ast *node);

/**
 * Get the correct action for this node
 * @param node
 * @return action function which should be executed for this node
 */
parseAction* get_infix_action(struct ast *node);

/**
 * Get the correct action for a node assuming we are parsing postfix notation
 * @param node
 * @return action function which should be executed for this node
 */
parseAction* get_postfix_action(struct ast *node);

#endif //POSTINFIX_PARSEACTION_H
