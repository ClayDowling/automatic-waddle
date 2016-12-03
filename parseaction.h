#ifndef POSTINFIX_PARSEACTION_H
#define POSTINFIX_PARSEACTION_H

#include "ast.h"
#include "parse_context.h"

/**
 * @file parseaction.h
 *
 * @brief action factories for parsing.
 *
 * Factories which will generate #parseAction functions to correctly handle each symbol found while parsing
 * a string.  Also possibly an example of taking abstraction to the point of absurdity.
 *
 * Also contains the meta-factory get_action_factory() which will generate an appropriate #actionFactory
 * based on the contents of the source expression.
 */

/**
 * Prototype for a function which will take an appropriate parser action for this node
 * @param node on which to take action
 * @param context parse_context which holds state for this run of the parser
 * @return 0 if the action completed successfully, something else if there was an error
 */
typedef int (parseAction)(struct ast *node, struct parse_context *context);

/**
 * Prototype for an action factory.  An action factory, given a node, will determine the
 * correct #parseAction function to process that node.
 */
typedef parseAction* (actionFactory)(struct ast *node);

/**
 * Get the correct action for this node.  This is an #actionFactory for processing infix expressions.
 * @param node
 * @return action function which should be executed for this node
 */
parseAction* get_infix_action(struct ast *node);

/**
 * Get the correct action for a node assuming we are parsing postfix notation.  This is an #actionFactory
 * for processing postfix (RPN) expressions.
 * @param node
 * @return action function which should be executed for this node
 */
parseAction* get_postfix_action(struct ast *node);

/**
 * Based on the source, return the correct #actionFactory for generating per-node actions.
 * @param source expression to be parsed
 * @return actionFactory which should be used to generate the actual actions.
 */
actionFactory *get_action_factory(const char *source);

/**
 * Safely apply an operator to available operands, signalling error if the operator cannot be applied.
 * This is a utility function used internally by #parseAction methods, but is also useful for other operations
 * which need to apply operators.
 * @param operator Operator to apply
 * @param context Parse context
 * @return 0 if the operators were applied successfully, 1 if there was an error.
 */
int apply_operator_to_operands(struct ast *operator, struct parse_context *context);
#endif //POSTINFIX_PARSEACTION_H
