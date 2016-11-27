#ifndef POSTINFIX_OPERATOR_H
#define POSTINFIX_OPERATOR_H

struct operator_t {
    char symbol;
    int precedence;
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
 * @param op
 * @return
 */
struct operator_t* operator_get(char op);

#endif //POSTINFIX_OPERATOR_H
