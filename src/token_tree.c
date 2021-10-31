#include "token_tree.h"
#include <stdlib.h>


token_tree *make_token_tree() {
	token_tree *tree = malloc(sizeof(token_tree));
	tree->children = malloc(TOKEN_TREE_INIT_SIZE * sizeof(void*));
	tree->used = 0;
	tree->size = TOKEN_TREE_INIT_SIZE;
	return tree;
}

void add_child(token_tree *parent, token_tree *tree) {
	if (parent->used == parent->size) {
		parent->children = realloc(parent->children, (parent->size * 2) * sizeof(void*));
		parent->size *= 2;
	}
	(parent->children)[parent->used - 1] = tree;
	parent->used += 1;
	tree->parent = parent;
	return;
}
