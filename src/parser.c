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
	ast_set_node(tree, node_make(program_n, -1));
	program_directive(tree, arr, table, lookahead);

	ast_add(tree, ast_make());
	if (node_array_get_node_type(arr, lookahead) == secondarydirective_n) {
		secondary_directive_list(tree, arr, table, lookahead);
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
	function(tree, arr, table, lookahead);
}

void function(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(program_directive_token, -1));

	tree = ast_get_last(tree);

	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
	match(arr, table, function_token, lookahead);

	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
	match(arr, table, identifier_token, lookahead);

	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
	match(arr, table, opening_bracket_token, lookahead);

	if (node_array_get_node_type(arr, *lookahead) == closing_bracket_token) {
		ast_add(tree, ast_make());
		ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
		match(arr, table, closing_bracket_token, lookahead);
	} else {
	parameter_list(tree, arr, table, lookahead);

	}
}


void functions(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {

}

void parameter(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	tree = ast_get_last(tree);
	type(tree, arr, table, lookahead);
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
	match(arr, table, identifier_token, lookahead);
	return;
}

void parameter_list(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	tree = ast_get_last(tree);
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(parameter_n, -1));
	parameter(tree, arr, table, lookahead);
	if (node_array_get_node_type(arr, *lookahead) == comma_token) {
		
	}
	ast = ast_get_parent(ast);
}

void type(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	tree = ast_get_last(tree);
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
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

void unop(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (node_array_get_node_type(arr, *lookahead) == increment_operator_token) {
		match(arr, table, increment_operator_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == decrement_operator_token) {
		match(arr, table, decrement_operator_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == not_token) {
		match(arr, table, not_token, lookahead);
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
}

void binop(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (node_array_get_node_type(arr, *lookahead) == plus_operator_token) {
		match(arr, table, plus_operator_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == minus_operator_token) {
		match(arr, table, minus_operator_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == multiplication_operator_token) {
		match(arr, table, multiplication_operator_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == division_operator_token) {
		match(arr, table, division_operator_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == mod_operator_token) {
		match(arr, table, mod_operator_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == pot_operator_token) {
		match(arr, table, pot_operator_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == gt_operator_token) {
		match(arr, table, gt_operator_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == lt_operator_token) {
		match(arr, table, lt_operator_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == le_operator_token) {
		match(arr, table, le_operator_token, lookahead);
	} else if (node_array_get_node_type(arr, *lookahead) == ge_operator_token) {
		match(arr, table, ge_operator_token, lookahead);
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
}

void program_directive(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(program_directive_token, -1));
	
	tree = ast_get_last(tree);

	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
	match(arr, table, program_directive_token, lookahead);

	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
	match(arr, table, identifier_token, lookahead);

	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
	match(arr, table, semicolon_token, lookahead);
	return;
}

void module_directive(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	tree = ast_get_last(tree);

	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));	
	match(arr, table, module_directive_token, lookahead);

	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
	match(arr, table, identifier_token, lookahead);

	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
	match(arr, table, semicolon_token, lookahead);
}

void module_directive_list(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	tree = ast_get_last(tree);
	if (node_array_get_node_type(arr, *lookahead) == module_directive_token) {
		module_directive(tree, arr, table, lookahead);
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
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
