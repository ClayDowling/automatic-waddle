#ifndef POSTINFIX_PARSER_H
#define POSTINFIX_PARSER_H

#include "ast.h"

/**
 * Take a source infix expression and convert it to an abstract syntax tree
 * @param source mathematical expression in infix notation
 * @return an Abstract Syntax Tree representing the equation in appropriate precedence.
 *         Caller is responsible for freeing with ast_release()
 */
struct ast* parse_infix(const char* source);

/**
 * Take a source postfix expression and convert it to an abstract syntax tree
 * @param source mathematical expression in postfix notation
 * @return an Abstract Syntax Tree representing the equation.  Caller is responsible
 *         for freeing with ast_release()
 */
struct ast* parse_postfix(const char* source);

#endif //POSTINFIX_PARSER_H
