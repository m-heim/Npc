#ifndef TOKEN_TREE_H
#define TOKEN_TREE_H

#include <stdlib.h>
#include "token.h"
#define TOKEN_TREE_INIT_SIZE 10
typedef struct {
	enum token_type token;
	// Pointer to the array of children
	token_tree **children;
	token_tree *parent;
	size_t used = 0;
	size_t size = TOKEN_TREE_INIT_SIZE;
} token_tree;

token_tree *new_token_tree(enum token_type token);

void add_child(token_tree *parent, token_tree *tree);

#endif