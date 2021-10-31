#ifndef TOKEN_TREE_H
#define TOKEN_TREE_H

#include "token.h"
#include <stdlib.h>
#define TOKEN_TREE_INIT_SIZE 10
typedef struct token_tree token_tree;
struct token_tree{
	token_type token;
	// Pointer to the array of children
	token_tree **children;
	token_tree *parent;
	unsigned int used;
	unsigned int size;
};

token_tree *make_token_tree();

void add_child(token_tree *parent, token_tree *tree);

#endif
