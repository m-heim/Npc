#include <stdio.h>
#include "ast.h"
#include "node.h"
#include "parser.h"
#include "scanner.h"
#include "symbol_table.h"

ast *parse_program(scanner_result res) {
	long *lookahead;
	*lookahead = 0;
	ast *tree = ast_make();
	printf("Parsing now\n");
	program(tree, res.node_array, res.table, lookahead);
	return tree;
}

void parse_syntax_err(long line) {
	printf("ERROR: line %ld\n", line);
}

void program(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	// set top node
	ast_set_node(tree, node_make(program_n, nont_c, -1));
	// match program directive
	program_directive(tree, arr, table, lookahead);
	// option
	if (node_array_get_node_type_class(arr, *lookahead) == sec_directive_c) {
		secondary_directive_list(tree, arr, table, lookahead);
	}

	functions(tree, arr, table, lookahead);
}

void function(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(function_n, nont_c ,-1));

	tree = ast_get_last(tree);

	match(tree, arr, table, function_token, lookahead);
	match(tree, arr, table, identifier_token, lookahead);
	match(tree, arr, table, opening_bracket_token, lookahead);

	if (node_array_get_node_type(arr, *lookahead) == closing_bracket_token) {
		match(tree, arr, table, closing_bracket_token, lookahead);
	} else {
		parameter_list(tree, arr, table, lookahead);
		match(tree, arr, table, closing_bracket_token, lookahead);
	}
	match(tree, arr, table, opening_c_bracket_token, lookahead);

	//cont;
}

// Parses multiple functions, but at least one.
void functions(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(functions_n, nont_c, -1));

	tree = ast_get_last(tree);

	if (node_array_get_node_type(arr, *lookahead) == function_token) {
		while (node_array_get_node_type(arr, *lookahead) == function_token) {
			function(tree, arr, table, lookahead);
		}
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
	return;
}

void parameter(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(parameter_n, nont_c, -1));

	tree = ast_get_last(tree);

	type(tree, arr, table, lookahead);

	match(tree, arr, table, identifier_token, lookahead);
	return;
}

void parameter_list(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(parameter_list_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	if(node_array_get_node_type_class(arr, *lookahead) == type_c) {
		while (node_array_get_node_type_class(arr, *lookahead) == type_c) {
			parameter(tree, arr, table, lookahead);
			//?
		}
		return;
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
}

void type(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(type_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_by_class(tree, arr, table, type_c, lookahead);
}

void unop(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(unop_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_by_class(tree, arr, table, unop_c, lookahead);
}

void binop(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(binop_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_by_class(tree, arr, table, binop_c, lookahead);
}

void program_directive(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(program_directive_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	match(tree, arr, table, program_directive_token, lookahead);
	match(tree, arr, table, identifier_token, lookahead);
	match(tree, arr, table, semicolon_token, lookahead);
	return;
}

void module_directive(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(module_directive_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	match(tree, arr, table, module_directive_token, lookahead);
	match(tree, arr, table, identifier_token, lookahead);
	match(tree, arr, table, semicolon_token, lookahead);
}

void include_directive(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(include_directive_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	match(tree, arr, table, module_directive_token, lookahead);
	include_directive_select(tree, arr, table, lookahead);
	match(tree, arr, table, semicolon_token, lookahead);
}

void include_directive_select(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(include_directive_subselect_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	if (node_array_get_node_type(arr, *lookahead) == identifier_token) {
		while (node_array_get_node_type(arr, *lookahead) == identifier_token) {
				match(tree, arr, table, identifier_token, lookahead);
				if(node_array_get_node_type(arr, *lookahead) == semicolon_token) {
					break;
				} else if (node_array_get_node_type(arr, *lookahead) == selector_token){
					match(tree, arr, table, selector_token, lookahead);
				} else {
					parse_syntax_err(symbol_table_get_line(table, *lookahead));
				}
		}
	}
}

void secondary_directive_list(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	
}


void match(ast *tree, node_array *arr, symbol_table *table, node_type type, long *lookahead) {
	printf("Matching %ld\n", *lookahead);
	if (node_array_get_node_type(arr, *lookahead) == type) {
		ast_add(tree, ast_make());
		ast_set_node(tree, node_array_get_node(arr, *lookahead));
		(*lookahead)++;
		printf("Lookahead now %ld\n", *lookahead);
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
	return;
}

void match_by_class(ast *tree, node_array *arr, symbol_table *table, node_type_class type, long *lookahead) {
	printf("Matching %ld\n", *lookahead);
	if (node_array_get_node_type_class(arr, *lookahead) == type) {
		ast_add(tree, ast_make());
		ast_set_node(tree, node_array_get_node(arr, *lookahead));
		(*lookahead)++;
		printf("Lookahead now %ld\n", *lookahead);
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
	return;
}
