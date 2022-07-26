/**
 * @file ast.h
 * @author MaximilianHeim@protonmail.com
 * @brief Ast contains the type and prototypes for working with abstract syntax trees
 * @version 0.1
 * @date 2022-04-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef AST_H
#define AST_H

#include "node.h"
#include <stdlib.h>
#define AST_INIT_SIZE 10
typedef struct ast ast;
/**
 * @brief The abstract syntax tree is a tree representation of the source program
 * 
 */
struct ast {
	node n;
	// Pointer to the array of children
	ast** children;
	ast* parent;
	long used;
	long size;
};

ast *ast_make();

/**
 * @brief 
 * 
 * @param parent 
 * @param tree 
 */
void ast_add(ast* parent, ast* tree);

// get the child at position x
ast* ast_get_child(ast* tree, long id);

// set the value of the ast
void ast_set_node(ast* tree, node* n);

// get the last child
ast* ast_get_last(ast* tree);

// get the parent
ast* ast_get_parent(ast* tree);

#endif
