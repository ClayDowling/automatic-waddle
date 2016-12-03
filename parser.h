#ifndef POSTINFIX_PARSER_H
#define POSTINFIX_PARSER_H

#include "ast.h"

/**
 * @file parser.h
 *
 * Operations related to parsing expressions.  Current expressions are very limited:
 *
 * * expressions may be in infix or postfix notation
 * * operands in the source expression may consist of single lower case letters (i.e. no numerals)
 * * operators are limited to *, /, +, -, and ^, with grouping in infix operations using parens.
 */

/**
 * \mainpage Postfix/Infix Parser
 *
 * Postfix and infix parser using Abstract Syntax Trees.  To use the parse, pass your source
 * expression to parse() and collect the parsed ast, then pass that AST to either ast_infix() or
 * ast_postfix() to render it in your chosen format.
 */

/**
 * Return an Abstract Syntax Tree containing the parsed results of the source expression.
 * @param source expression to be parsed, in infix or postfix notation
 * @return struct ast* representing the expression, or NULL if there were errors.
 */
struct ast* parse(const char *source);

#endif //POSTINFIX_PARSER_H
