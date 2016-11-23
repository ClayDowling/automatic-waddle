#ifndef _AST_H_
#define _AST_H_

/**
 * Represents a single variable or operation in an Abstract Syntax Tree
 */
struct ast {
	char symbol;		/** Symbol represented by this node */
	struct ast *parent;	/** Parent node, NULL if top of tree */
	struct ast *left;	/** Node most immediately preceeding */
	struct ast *right;	/** Node most immediately following */
};

/**
 * Allocate and initialize an AST node
 *
 * @param symb Symbol represented by this node
 *
 * @return sturct ast* newly created node.
 */
struct ast* ast_create(char symb);

/**
 * Release an AST node
 *
 * @param top Top of the tree which will be released
 */
void ast_release(struct ast* top);

/**
 * Attach a child node to the left of a parent node, and 
 * set the appropriate parent link
 *
 * @param parent Parent AST node
 * @param child AST node which will be left of parent
 */
void ast_attach_left(struct ast *parent, struct ast* child);

#endif
