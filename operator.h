#ifndef POSTINFIX_OPERATOR_H
#define POSTINFIX_OPERATOR_H

/**
 * @file operator.h
 *
 * Provides access to the static operators which are understood by the parser.  Pointers to these operators
 * should be used to reference them, rather than copying on the stack.  This allows simple pointer
 * comparisons, rather than defining an equality operator.  To see if the operation for an AST node is a plus
 * sign then, you would write something similar to
 * @code
 * if (&OP_PLUS == node->operator)
 * @endcode
 */

struct operator_t {
    char symbol;    /** Symbol which corresponds to this operator, or \\0 if there are many matches */
    int precedence; /** Operator precedence, with higher precedence meaning the operator should be grabbed first */
};

extern struct operator_t OP_VARIABLE;
extern struct operator_t OP_LEFTPAREN;
extern struct operator_t OP_RIGHTPAREN;
extern struct operator_t OP_PLUS;
extern struct operator_t OP_MINUS;
extern struct operator_t OP_TIMES;
extern struct operator_t OP_DIVIDE;
extern struct operator_t OP_EXPONENT;

/**
 * Return a pointer to an operator_t representing this action
 * @param op symbol which wish to find a matching operator for.
 * @return operator_t matching this symbol.
 */
struct operator_t* operator_get(char op);

#endif //POSTINFIX_OPERATOR_H
