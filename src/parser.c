#include <stdio.h>
#include "ast.h"
#include "node.h"
#include "parser.h"
#include "scanner.h"

ast *parse_program(scanner_result res) {
	long l = 0;
	long *lookahead = &l;
	ast *tree = ast_make();
	printf("Parsing now\n");
	program(tree, res.node_array, res.table, lookahead);
	return tree;
}

void parse_syntax_err(long line) {
	printf("ERROR: line %ld\n", line);
}

void program(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	program_directive(tree, arr, table, lookahead);
	secondary_directive_list(tree, arr, table, lookahead);
	main_function(tree, arr, table, lookahead);
}

void function(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	type(tree, arr, table, lookahead);
	match(arr, table, identifier_token, lookahead);
	match(arr, table, opening_bracket_token, lookahead);
	parameter_list(tree, arr, table, lookahead);
}

void parameter_list(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	
}

void type(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (node_array_get_node_type(arr, *lookahead) == int_type_type_token) {
		match(arr, table, int_type_type_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == char_type_type_token) {
		match(arr, table, char_type_type_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == string_type_type_token) {
		match(arr, table, string_type_type_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == float_type_type_token) {
		match(arr, table, float_type_type_token, lookahead);
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
}

void program_directive(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	printf("1\n");
	match(arr, table, program_directive_token, lookahead);
	printf("2\n");
	ast_add(tree, ast_make());
	printf("3\n");
	match(arr, table, identifier_token, lookahead);
	printf("4\n");
	ast_add(tree, ast_make());
	printf("5\n");
	match(arr, table, semicolon_token, lookahead);
	printf("6\n");
	ast_add(tree, ast_make());
	return;
}

void secondary_directive_list(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	
}

void match(node_array *arr, symbol_table *table, node_type type, long *lookahead) {
	printf("Matching %ld\n", *lookahead);
	if (node_array_get_node_type(arr, *lookahead) == type) {
		(*lookahead)++;
		printf("Lookahead now %ld\n", *lookahead);
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
	return;
}
