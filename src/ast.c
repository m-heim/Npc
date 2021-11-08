#include "ast.h"
#include <stdlib.h>
#include <stdio.h>


ast *ast_make() {
	ast *tree = malloc(sizeof(ast));
	tree->children = malloc(AST_INIT_SIZE * sizeof(void*));
	tree->used = 0;
	tree->size = AST_INIT_SIZE;
	return tree;
}

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
