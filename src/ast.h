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

// make a new abstract syntax tree
ast *ast_make();

// add a new ast to the parent
void ast_add(ast *parent, ast *tree);

// get the child at position x
ast *ast_get_child(ast *tree, long id);

// set the value of the ast
void ast_set_node(ast *tree, node *n);

// get the last child
ast *ast_get_last(ast *tree);

// get the parent
ast *ast_get_parent(ast *tree);

#endif
