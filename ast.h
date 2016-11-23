#ifndef _AST_H_
#define _AST_H_

struct ast {
	char symbol;
	struct ast *parent;
	struct ast *left;
	struct ast *right;
};

struct ast* ast_create(char symb);


#endif
