#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdlib.h>
#include "ast.h"
#include "operator.h"
#include "buffer.h"

#define BUFFER_SIZE 4096

struct ast* ast_create(char symb)
{
	struct ast *node;

	node = (struct ast*)calloc(1, sizeof(struct ast));
	node->symbol = symb;
    node->operator = operator_get(symb);
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

void ast_traverse_inorder(struct ast *top, traverseCallback callback, void *userdata)
{
    struct ast *current = top;

    while(current) {
        if (current->left && !current->left->visited) {
            current = current->left;
            continue;
        }
        if (!current->visited) {
            callback(current, userdata);
            current->visited = 1;
        }
        if (current->right && !current->right->visited) {
            current = current->right;
            continue;
        }

        if (current->left) {
            current->left->visited = 0;
        }
        if (current->right) {
            current->right->visited = 0;
        }
        current = current->parent;
    }
    if (top) {
        top->visited = 0;
    }
}

void aggregate_tree(struct ast *node, void *ptrbuffer)
{
    struct buffer *buf = (struct buffer*)ptrbuffer;
    buffer_append(buf, node->symbol);
}

int needs_parent(struct ast *parent, struct ast *child)
{
    if (NULL == parent || NULL == child) {
        return 0;
    }
    if (parent->operator == &OP_VARIABLE || child->operator == &OP_VARIABLE) {
        return 0;
    }
    if (parent->operator->precedence > child->operator->precedence) {
        return 1;
    }
    return 0;
}

int i_am_a_leaf(struct ast *node)
{
    if (NULL == node) {
        return 0;
    }
    if (node->operator != &OP_VARIABLE) {
        return 0;
    }
    if (NULL == node->parent) {
        return 0;
    }
}

int i_am_a_left_leaf(struct ast *node)
{
    if (i_am_a_leaf(node)) {
        if (!node->parent->visited) {
            return 1;
        }
    }
    return 0;
}

int i_am_a_right_leaf(struct ast *node)
{
    if (i_am_a_leaf(node)) {
        if (node->parent->visited) {
            return 1;
        }
    }
    return 0;
}

void add_parens(struct ast *node, struct buffer *buf)
{
    struct ast *parent;
    struct ast *child;
    int leftnode = i_am_a_left_leaf(node);
    char symbol;

    if (leftnode) symbol = '(';
    else symbol = ')';

    if (node->parent && node->parent->parent) {
        child = node->parent;
        parent = node->parent->parent;

        while(parent && parent->operator->precedence > child->operator->precedence) {
            buffer_append(buf, symbol);
            if (leftnode == parent->visited) {
                break;
            }
            child = parent;
            parent = parent->parent;
        }
    }
}

void aggregate_infix_tree(struct ast *node, void *ptrbuffer)
{
    struct buffer *buf = (struct buffer*)ptrbuffer;

    if (i_am_a_left_leaf(node)) {
        add_parens(node, buf);
    }

    buffer_append(buf, node->symbol);

    if (i_am_a_right_leaf(node)) {
        add_parens(node, buf);
    }
}

char *ast_postfix(struct ast *top)
{
    struct buffer *buf = buffer_create(BUFFER_SIZE);
    char *result;

    ast_traverse_postorder(top, aggregate_tree, buf);

    result = buffer_as_string(buf);
    buffer_release(buf);

    return result;
}

char *ast_infix(struct ast *top)
{
    struct buffer *buf = buffer_create(BUFFER_SIZE);
    char *result;

    ast_traverse_inorder(top, aggregate_infix_tree, buf);

    result = buffer_as_string(buf);
    buffer_release(buf);
    return result;
}
