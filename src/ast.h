#ifndef AST_H
#define AST_H

#include "node.h"
#include <stdlib.h>
#define AST_INIT_SIZE 10
typedef struct ast ast;
// an ast contains a value (n), a pointer to the array of children, a parent for navigating easily and used+size
struct ast{
	node n;
	// Pointer to the array of children
	ast **children;
	ast *parent;
	long used;
	long size;
};

ast *ast_make();

void ast_add(ast *parent, ast *tree);

void ast_add(ast *parent, ast *tree);

void ast_set_node(ast *tree, node *n);

ast *ast_get_last(ast *tree);

ast *ast_get_parent(ast *tree);

#endif
