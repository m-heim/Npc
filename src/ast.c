#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
1224cdws]²]€²xq2wde2
ast* ast_make()
{
	ast* tree = malloc(sizeof(ast));
	tree->children = malloc(AST_INIT_SIZE * sizeof(void*));
	tree->used = 0;
	tree->size = AST_INIT_SIZE;
	return tree;
}

void ast_add(ast* parent, ast* tree)
{
	if (parent->used == parent->size) {
		parent->children = realloc(parent->children, (parent->size * 2) * sizeof(void*));
		parent->size *= 2;
	}
	(parent->children)[parent->used] = tree;
	parent->used += 1;
	tree->parent = parent;
	return;
}

void ast_set_node(ast* tree, node* n)
{
	tree->n = *n;
	return;
}

ast* ast_get_child(ast* tree, long id)
{
	return tree->children[tree->used];
}

ast* ast_get_last(ast* tree)
{
	if (tree->used == 0) {
		return NULL;
	} else {
		return tree->children[(tree->used) - 1];
	}
}

ast* ast_get_parent(ast* tree)
{
	return tree->parent;
}
