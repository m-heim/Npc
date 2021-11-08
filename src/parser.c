#include <stdio.h>
#include "token_tree.h"
#include "token.h"
#include "parser.h"
#include "scanner.h"

token_tree *parse_program(scanner_result *res) {
	long *lookahead = 0;
	token_tree *tree = token_tree_make();
	program(tree, res->tkn_array, res->table, lookahead);
	return tree;
}

void parse_syntax_err(long line) {
	printf("ERROR: line %ld", line);
}

void program(token_tree *tree, token_array *arr, symbol_table *table, long *lookahead) {
	program_directive(tree, arr, table, lookahead);
	

void program_directive(token_tree *tree, token_array *arr, symbol_table *table, long *lookahead) {
	match(arr, table, program_directive_token, lookahead);
	token_tree_add(tree, token_tree_make(token_array_get_token(arr, lookahead - 1)));
	match(arr, table, identifier_token, lookahead);
	token_tree_add(tree, token_tree_make(token_array_get_token(arr, lookahead - 1)));
	match(arr, table, semicolon_token, lookahead);
	token_tree_add(tree, token_tree_make(token_array_get_token(arr, lookahead - 1)));
	return;
}

void secondary_directive_list(token_tree *tree, token_array *arr, symbol_table *table, long *lookahead) {
	
}

void match(token_array *arr, symbol_table *table, token_type type, long *lookahead) {
	if (token_array_get_token_type(arr, *lookahead) == type) {
		*lookahead++;
	} else {
		parse_syntax_err(symbol_table_get_line(*lookahead));
	}
	return;
}
