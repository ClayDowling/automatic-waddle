#ifndef POSTINFIX_PARSER_H
#define POSTINFIX_PARSER_H

#include "ast.h"

/**
 * Take a source infix expression and convert it to an abstract syntax tree
 * @param source mathematical expression in infix notation
 * @return an Abstract Syntax Tree representing the equation is appropriate precedence
 */
struct ast* parse_infix(const char* source);

#endif //POSTINFIX_PARSER_H
