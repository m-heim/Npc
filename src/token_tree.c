#include "token_tree.h"
#include <stdlib.h>


token_tree *make_token_tree() {
	token_tree *tree = malloc(sizeof(token_tree));
	tree->children = malloc(TOKEN_TREE_INIT_SIZE * 8);
	return tree;
}

void add_child(token_tree *parent, token_tree *tree) {
	if (parent->used == parent->size) {
		realloc(*(parent->children), parent->size * 2);
		parent->size *= 2;
	}
	*(parent->children)[parent->used] = token_tree;
	parent->used += 1;
	tree->parent = parent;
	return;
}

