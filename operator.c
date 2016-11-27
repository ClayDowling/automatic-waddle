#include <stdlib.h>

#include "operator.h"

struct operator_t OP_VARIABLE = {0, 0};
struct operator_t OP_LEFTPAREN = {'(', 0};
struct operator_t OP_RIGHTPAREN = {')', 0};
struct operator_t OP_PLUS = {'+', 1};
struct operator_t OP_MINUS = {'-', 2};
struct operator_t OP_TIMES = {'*', 3};
struct operator_t OP_DIVIDE = {'/', 4};
struct operator_t OP_EXPONENT = {'^', 5};

struct operator_t* operator_get(char op)
{
    struct operator_t *operators[] = {
            &OP_LEFTPAREN,
            &OP_RIGHTPAREN,
            &OP_PLUS,
            &OP_MINUS,
            &OP_TIMES,
            &OP_DIVIDE,
            &OP_EXPONENT,
            NULL
    };
    struct operator_t *thisop = &OP_VARIABLE;

    for(int i = 0; operators[i]; ++i) {
        if (operators[i]->symbol == op) {
            thisop = operators[i];
        }
    }
    return thisop;
}
