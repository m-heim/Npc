#include <token_tree.h>

token_tree *new_token_tree(enum token_type token) {
	token_tree *tree = malloc(sizeof(token_tree));
	tree->token = token;
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

