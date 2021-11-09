#include "ast.h"
#include <stdlib.h>
#include <stdio.h>


// Make a new empty ast
ast *ast_make() {
	ast *tree = malloc(sizeof(ast));
	tree->children = malloc(AST_INIT_SIZE * sizeof(void*));
	tree->used = 0;
	tree->size = AST_INIT_SIZE;
	return tree;
}

// Add a new tree to the ast
void ast_add(ast *parent, ast *tree) {
	if (parent->used == parent->size) {
		parent->children = realloc(parent->children, (parent->size * 2) * sizeof(void*));
		parent->size *= 2;
	}
	(parent->children)[parent->used] = tree;
	parent->used += 1;
	tree->parent = parent;
	return;
}

// Set the node of the ast
void ast_set_node(ast *tree, node *n) {
	tree->n = *n;
	return;
}

// Get a pointer to the last ast, returns NULL if the tree doesn\'t have any children
ast *ast_get_last(ast *tree) {
	if (tree->used == 0) {
		return NULL;
	} else {
		return tree->children[(tree->used) - 1];
	}
}

// Get the parent of the ast
ast *ast_get_parent(ast *tree) {
	return tree->parent;
}
