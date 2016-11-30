#ifndef POSTINFIX_PARSER_H
#define POSTINFIX_PARSER_H

#include "ast.h"

/**
 * Return an Abstract Syntax Tree containing the parsed results of the source expression.
 * @param source expression to be parsed, in infix or postfix notation
 * @return struct ast* representing the expression
 */
struct ast* parse(const char *source);

#endif //POSTINFIX_PARSER_H
