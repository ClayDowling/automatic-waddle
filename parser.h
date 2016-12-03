#ifndef POSTINFIX_PARSER_H
#define POSTINFIX_PARSER_H

#include "ast.h"

/**
 * @file parser.h
 *
 * @brief Main entry method for expression parsing.
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
 *
 * To add the parser library to your program, include the path to the generated libpostinfix.a
 * to your library path (typically -L/path/to/postinfix) and the library itself to the list of
 * libraries to be linked into your program (e.g. -lpostinfix)
 *
 * When rendering an expression, understand that the rendered expression is guaranteed to be
 * equivalent to the source expression, but may not be identical.  Infix notation in particular
 * allows a good deal of flexibility, so excess parens may not be present in the rendered expression.
 * Rendered postfix expressions may also vary, in that the renderer attempts to push operators into
 * the output stream as soon as possible, but it is perfectly valid to push operators until later
 * in the stream.
 */

/**
 * Return an Abstract Syntax Tree containing the parsed results of the source expression.
 * @param source expression to be parsed, in infix or postfix notation
 * @return struct ast* representing the expression, or NULL if there were errors.
 */
struct ast* parse(const char *source);

#endif //POSTINFIX_PARSER_H
