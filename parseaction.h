#ifndef POSTINFIX_PARSEACTION_H
#define POSTINFIX_PARSEACTION_H

#include "ast.h"
#include "parse_context.h"

/**
 * Prototype for a function which will take an appropriate parser action for this node
 * @param node on which to take action
 * @param context parse_context which holds state for this run of the parser
 * @return 0 if the action completed successfully, something else if there was an error
 */
typedef int (parseAction)(struct ast *node, struct parse_context *context);

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

/**
 * Based on the source, return the correct factory for generating per-node actions.
 * @param source expression to be parsed
 * @return actionFactory which should be used to generate the actual actions.
 */
actionFactory *get_action_factory(const char *source);

#endif //POSTINFIX_PARSEACTION_H
