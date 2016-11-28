#ifndef _AST_H_
#define _AST_H_

#include "operator.h"

/**
 * Represents a single variable or operation in an Abstract Syntax Tree
 */
struct ast {
	char symbol;		/** Symbol represented by this node */
	int visited;		/** Has the node been visited during traversal */
	struct operator_t *operator; /** Cached operator */
	struct ast *parent;	/** Parent node, NULL if top of tree */
	struct ast *left;	/** Node most immediately preceeding */
	struct ast *right;	/** Node most immediately following */
};

typedef void (*traverseCallback)(struct ast* node, void* userdata);

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

/**
 * Attach a child node to the right of a parent node, and 
 * set the appropriate parent link
 *
 * @param parent Parent AST node
 * @param child AST node which will be right of parent
 */
void ast_attach_right(struct ast *parent, struct ast* child);

/**
 * Perform an interative, post-order traversal of the tree pointed to by top.
 * i.e. take action on both the left and right nodes, then take action on the
 * current node.
 * @param top Tree to traverse.
 * @param callback function which will be called on each node.
 * @param userdata user supplied data which will be supplied as the second
 *        parameter to the callback function.
 */
void ast_traverse_postorder(struct ast *top, traverseCallback callback, void *userdata);

/**
 * Perform an iterative, in-order traversal of the tree pointed to by top.
 * i.e. take action on the nodes on the left.  Take action on this node.  Take action
 * on the nodes on the right.
 * @param top Tree to traverse
 * @param callback function which will be called on each node.
 * @param userdata user supplied data which will be supplied as the second
 *        parameter to the callback function.
 */
void ast_traverse_inorder(struct ast *top, traverseCallback callback, void *userdata);

/**
 * String the symbols out in the order they were gathered via an ast_traverse_postorder
 * @param top
 * @return string value of the aggregated symbols.  Caller is responsible for freeing.
 */
char *ast_postfix(struct ast *top);

/**
 * Represent the tree as infix notation.
 * @param top Tree to be represented
 * @return string value of the tree as infix notation.  Caller is responsible for freeing.
 */
char *ast_infix(struct ast *top);

#endif
