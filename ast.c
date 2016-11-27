#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdlib.h>
#include "ast.h"
#include "operator.h"

struct ast* ast_create(char symb)
{
	struct ast *node;

	node = (struct ast*)calloc(1, sizeof(struct ast));
	node->symbol = symb;
	return node;
}

void ast_release(struct ast* top)
{
	struct ast *left;
	struct ast *right;

	if (NULL == top) {
		return;
	}

	left = top->left;
	right = top->right;

	free(top);
	ast_release(left);
	ast_release(right);
}

void ast_attach_left(struct ast *parent, struct ast *child)
{
	parent->left = child;
	child->parent = parent;
}

void ast_attach_right(struct ast *parent, struct ast *child)
{
	parent->right = child;
	child->parent = parent;
}

void ast_traverse_postorder(struct ast *top, traverseCallback callback, void *userdata)
{
    struct ast *current;
    struct ast *parent;
    struct ast *left;
    struct ast *right;

    current = top;
    while(NULL != current) {
        if (current->left && !current->left->visited) {
            current = current->left;
            continue;
        } else if (current->right && !current->right->visited) {
            current = current->right;
            continue;
        }

        if (!current->visited) {
            current->visited = 1;
            callback(current, userdata);
        }

        if (current->left) {
            current->left->visited = 0;
        }
        if (current->right) {
            current->right->visited = 0;
        }
        current = current->parent;
    }

}

char postfix_buffer[4096];
int postfix_idx = 0;

void aggregate_tree(struct ast *node, void *notused)
{
    if (postfix_idx < sizeof(postfix_buffer))
        postfix_buffer[postfix_idx++] = node->symbol;
}

char *ast_postfix(struct ast *top)
{
    postfix_idx = 0;
    memset(postfix_buffer, 0, sizeof(postfix_buffer));

    ast_traverse_postorder(top, aggregate_tree, NULL);

    return strdup(postfix_buffer);
}
