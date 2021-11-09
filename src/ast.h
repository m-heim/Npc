#ifndef AST_H
#define AST_H

#include "node.h"
#include <stdlib.h>
#define AST_INIT_SIZE 10
typedef struct ast ast;
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

#endif
