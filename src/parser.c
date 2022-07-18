#include "parser.h"
#include "ast.h"
#include "node.h"
#include "scanner.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>

int parser_debug = 1;

parser_result parser_result_make(ast* tree, symbol_table* table, typetable* type_table)
{
	parser_result res;
	res.type_table = type_table;
	res.table = table;
	res.tree = tree;
	return res;
}

parser_result parse_program(scanner_result res)
{
	typetable* type_table = typetable_make();
	symbol_table* symbol_table = res.table;
	long l = 0;
	long* position = &l;
	ast* tree = ast_make();
	program(tree, res.node_array, res.table, position);
	return parser_result_make(tree, symbol_table, type_table);
}

void parse_syntax_err(symbol_table* table, long* position, char* err)
{
	printf("ERROR: line %ld on token %s, %s\n", symbol_table_get_line(table, *position), symbol_table_get_value(table, *position), err);
	_Exit(1);
}

void program(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing PROGRAM now\n");
	}
	// set top node
	ast_set_node(tree, node_make(program_n, nont_c, -1));
	// match program directive
	program_directive(tree, arr, table, position);
	// option
	if (node_array_get_node_type_class(arr, *position) == sec_directive_c) {
		secondary_directive_list(tree, arr, table, position);
	}

	functions(tree, arr, table, position);
}

void function(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing FUNCTION\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(function_n, nont_c, -1));

	tree = ast_get_last(tree);

	type(tree, arr, table, position);
	match(tree, arr, table, identifier_token, position);
	match_no_append(tree, arr, table, opening_bracket_token, position);

	if (node_array_get_node_type(arr, *position) == closing_bracket_token) {
		match_no_append(tree, arr, table, closing_bracket_token, position);
	} else {
		parameter_list(tree, arr, table, position);
		match_no_append(tree, arr, table, closing_bracket_token, position);
	}
	block(tree, arr, table, position);

	// cont;
}

void type(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing TYPES\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(type_n, type_c, -1));

	tree = ast_get_last(tree);

	match_by_class(tree, arr, table, type_c, position);
	if (node_array_get_node_type(arr, *position) == opening_s_bracket_token) {
		while (node_array_get_node_type(arr, *position) == opening_s_bracket_token) {
			match_no_append(tree, arr, table, opening_s_bracket_token, position);
			if (node_array_get_node_type(arr, *position) == int_literal)  {
				match(tree, arr, table, int_literal, position);
			}
			
			match_no_append(tree, arr, table, closing_s_bracket_token, position);
		}
	}
}

// Parses multiple functions, but at least one.
void functions(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing FUNCTIONS\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(functions_n, nont_c, -1));

	tree = ast_get_last(tree);
	do {
		function(tree, arr, table, position);
	} while (node_array_get_node_type_class(arr, *position) == type_c);
	return;
}

void parameter(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing PARAM\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(parameter_n, nont_c, -1));

	tree = ast_get_last(tree);

	type(tree, arr, table, position);

	match(tree, arr, table, identifier_token, position);
	return;
}

void parameter_list(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing PARAMETER LIST\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(parameter_list_n, nont_c, -1));

	tree = ast_get_last(tree);
	parameter(tree, arr, table, position);
	while (node_array_get_node_type(arr, *position) == comma_token) {
		if (node_array_get_node_type(arr, *position) == comma_token) {
			match_no_append(tree, arr, table, comma_token, position);
		}
		parameter(tree, arr, table, position);
	}
	return;
}

void unop(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing UNOP\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(unop_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_by_class(tree, arr, table, unop_c, position);
}

void binop(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing BINOP\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(binop_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_by_class(tree, arr, table, binop_c, position);
}

void program_directive(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing PROGRAM DIRECTIVE\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(program_directive_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_no_append(tree, arr, table, program_directive_token, position);
	match(tree, arr, table, identifier_token, position);
	if (parser_debug) {
		printf("done Parsing PROGRAM DIRECTIVE\n");
	}
	return;
}

void module_directive(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing MODULE DIRECTIVE\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(module_directive_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_no_append(tree, arr, table, module_directive_token, position);
	match(tree, arr, table, identifier_token, position);
}

void include_directive(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing INC DIRECTIVE\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(include_directive_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_no_append(tree, arr, table, include_directive_token, position);
	include_directive_select(tree, arr, table, position);
}

void if_statement(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing IF\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(if_statement_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_no_append(tree, arr, table, if_keyword_token, position);
	match_no_append(tree, arr, table, opening_bracket_token, position);

	expression(tree, arr, table, position);

	match_no_append(tree, arr, table, closing_bracket_token, position);

	block(tree, arr, table, position);

	if (parser_debug) {
		printf("Parsing IF done\n");
	}
}

void return_statement(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing return statement\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(return_statement_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_no_append(tree, arr, table, return_keyword_token, position);
	// should also be able to return statement?
	expression(tree, arr, table, position);

	if (parser_debug) {
		printf("Parsing return statement done\n");
	}
}

void for_statement(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing for statement\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(for_statement_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_no_append(tree, arr, table, for_keyword_token, position);
	// should also be able to return statement?

	match_no_append(tree, arr, table, opening_bracket_token, position);
	declaration(tree, arr, table, position);
	match_no_append(tree, arr, table, semicolon_token, position);
	expression(tree, arr, table, position);
	match_no_append(tree, arr, table, semicolon_token, position);
	expression(tree, arr, table, position);
	match_no_append(tree, arr, table, closing_bracket_token, position);

	block(tree, arr, table, position);

	if (parser_debug) {
		printf("Parsing for statement done\n");
	}
}

void assignment(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing Assignment\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(if_statement_n, nont_c, -1));

	tree = ast_get_last(tree);

	var(tree, arr, table, position);

	match_by_class(tree, arr, table, assign_c, position);

	expression(tree, arr, table, position);
}

void statement(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing Statement\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(statement_n, nont_c, -1));

	tree = ast_get_last(tree);

	if (node_array_get_node_type(arr, *position) == if_keyword_token) {
		if_statement(tree, arr, table, position);
	} else if (node_array_get_node_type_class(arr, *position) == type_c) {
		declaration(tree, arr, table, position);
	} else if (node_array_get_node_type(arr, *position) == for_keyword_token) {
		for_statement(tree, arr, table, position);
	} else if (node_array_get_node_type(arr, *position) == identifier_token) {
		if (node_array_get_node_type(arr, *position + 1) == opening_bracket_token) {
			fun_call(tree, arr, table, position);
		} else if (node_array_get_node_type_class(arr, *position) == type_c) {
			declaration(tree, arr, table, position);
		}
	} else if (node_array_get_node_type(arr, *position) == return_keyword_token) {
		return_statement(tree, arr, table, position);
	}
	if (parser_debug) {
		printf("Parsing Statement done.\n");
	}
}

void simple_expression(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing simple exp\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(simple_expression_n, nont_c, -1));

	tree = ast_get_last(tree);

	term(tree, arr, table, position);

	if (node_array_get_node_type(arr, *position) == plus_operator_token) {
		match(tree, arr, table, plus_operator_token, position);
		simple_expression(tree, arr, table, position);
	} else if (node_array_get_node_type(arr, *position) == minus_operator_token) {
		match(tree, arr, table, minus_operator_token, position);
		simple_expression(tree, arr, table, position);
	}
}

void expression(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing Exp\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(expression_n, nont_c, -1));

	tree = ast_get_last(tree);

	simple_expression(tree, arr, table, position);

	if (node_array_get_node_type_class(arr, *position) == relop_c) {
		match_by_class(tree, arr, table, relop_c, position);
		simple_expression(tree, arr, table, position);
	}

	if (parser_debug) {
		printf("Parsing Exp done.\n");
	}
}

void term(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing terms\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(term_n, nont_c, -1));

	tree = ast_get_last(tree);

	factor(tree, arr, table, position);

	if (node_array_get_node_type(arr, *position) == multiplication_operator_token) {
		match(tree, arr, table, multiplication_operator_token, position);
		term(tree, arr, table, position);
	} else if (node_array_get_node_type(arr, *position) == division_operator_token) {
		match(tree, arr, table, division_operator_token, position);
		term(tree, arr, table, position);
	}
}

void var(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing var\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(if_statement_n, nont_c, -1));

	tree = ast_get_last(tree);

	match(tree, arr, table, identifier_token, position);
	if (node_array_get_node_type(arr, *position) == opening_s_bracket_token) {
		match_no_append(tree, arr, table, opening_s_bracket_token, position);
		expression(tree, arr, table, position);
		match_no_append(tree, arr, table, closing_s_bracket_token, position);
	}
}

void declaration(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing Decl\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(declaration_n, nont_c, -1));

	tree = ast_get_last(tree);

	type(tree, arr, table, position);
	match(tree, arr, table, identifier_token, position);
	if (node_array_get_node_type(arr, *position) == assignment_token) {
		match(tree, arr, table, assignment_token, position);
		expression(tree, arr, table, position);
	}
}

void fun_call(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing Functioncall\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(function_call_n, nont_c, -1));

	tree = ast_get_last(tree);

	match(tree, arr, table, identifier_token, position);

	match_no_append(tree, arr, table, opening_bracket_token, position);

	if (node_array_get_node_type(arr, *position) != opening_bracket_token) {
		argument_list(tree, arr, table, position);
	}
	match_no_append(tree, arr, table, closing_bracket_token, position);
}

void argument(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing Argument\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(argument_n, nont_c, -1));

	tree = ast_get_last(tree);

	expression(tree, arr, table, position);
}

void argument_list(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing Argumentlist\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(argument_list_n, nont_c, -1));

	tree = ast_get_last(tree);
	node_type next = node_array_get_node_type(arr, *position);

	do {
		argument(tree, arr, table, position);
		next = node_array_get_node_type(arr, *position);
		if (next == comma_token) {
			match_no_append(tree, arr, table, comma_token, position);
		}
	} while (next == comma_token);
}

void factor(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing Factor\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(factor_n, nont_c, -1));

	tree = ast_get_last(tree);

	switch (node_array_get_node_type(arr, *position)) {
	case not_token:
		break;
	case increment_operator_token:
		break;
	case decrement_operator_token:
		break;
	case opening_bracket_token:
		match_no_append(tree, arr, table, opening_bracket_token, position);
		expression(tree, arr, table, position);
		match_no_append(tree, arr, table, closing_bracket_token, position);
		break;
	case identifier_token:
		if (node_array_get_node_type(arr, *position + 1) == opening_bracket_token) {
			fun_call(tree, arr, table, position);
		} else if (node_array_get_node_type(arr, *position + 1) == increment_operator_token) {
			var(tree, arr, table, position);
			match(tree, arr, table, increment_operator_token, position);
		} else if (node_array_get_node_type(arr, *position + 1) == decrement_operator_token) {
			var(tree, arr, table, position);
			match(tree, arr, table, decrement_operator_token, position);
		} else {
			var(tree, arr, table, position);
		}
		break;
	case float_literal:
		match(tree, arr, table, float_literal, position);
		break;
	case string_literal:
		match(tree, arr, table, string_literal, position);
		break;
	case int_literal:
		match(tree, arr, table, int_literal, position);
		break;
	case char_literal:
		match(tree, arr, table, char_literal, position);
		break;

	default:
		break;
	}

	if (parser_debug) {
		printf("Parsing Factor done\n");
	}
}

void block(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing block\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(block_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_no_append(tree, arr, table, opening_c_bracket_token, position);

	while (node_array_get_node_type(arr, *position) != closing_c_bracket_token) {
		statement(tree, arr, table, position);
		match_no_append(tree, arr, table, semicolon_token, position);
	}

	match_no_append(tree, arr, table, closing_c_bracket_token, position);
	if (parser_debug) {
		printf("Parsing block done.\n");
	}
}

void include_directive_select(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing DIR SELECTT\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(include_directive_subselect_n, nont_c, -1));

	tree = ast_get_last(tree);
	do {
		match(tree, arr, table, identifier_token, position);
		if (node_array_get_node_type(arr, *position) == selector_token) {
			match_no_append(tree, arr, table, selector_token, position);
		}
		// maybe change this
	} while (node_array_get_node_type(arr, *position) == identifier_token);

	if (parser_debug) {
		printf("Parsing DIR SELECTT done.\n");
	}
}

void secondary_directives(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing SEC DIR\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(secondarydirective_n, nont_c, -1));

	tree = ast_get_last(tree);

	switch (node_array_get_node_type(arr, *position)) {
	case include_directive_token:
		include_directive(tree, arr, table, &*position);
		break;
	case macro_directive_token:
		// impleme
		break;
	default:
		_Exit(1);
	}
}

void secondary_directive_list(ast* tree, node_array* arr, symbol_table* table, long* position)
{
	if (parser_debug) {
		printf("Parsing SEC DIR LIST\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(secondarydirective_list_n, nont_c, -1));

	tree = ast_get_last(tree);

	do {
		secondary_directives(tree, arr, table, position);
	} while (node_array_get_node_type_class(arr, *position) == sec_directive_c);
}

void print_tree(ast* tree, int depth)
{
	int i;
	for (i = 0; i < depth; i++) {
		printf("  ");
	}
	printf("> %s\n", node_type_get_canonial(tree->n.type));
	for (i = 0; i < tree->used; i++) {
		print_tree(tree->children[i], depth + 1);
	}
}

void match(ast* tree, node_array* arr, symbol_table* table, node_type type, long* position)
{
	printf("Matching %s at %ld\n", node_type_get_canonial(type), *position);
	if (node_array_get_node_type(arr, *position) == type) {
		ast_add(tree, ast_make());
		ast_set_node(ast_get_last(tree), node_array_get_node(arr, *position));
		(*position)++;
	} else {
		parse_syntax_err(table, position, "expected differently");
	}
	return;
}

void match_no_append(ast* tree, node_array* arr, symbol_table* table, node_type type, long* position)
{
	printf("Matching %s at %ld\n", node_type_get_canonial(type), *position);
	if (node_array_get_node_type(arr, *position) == type) {
		(*position)++;
	} else {
		parse_syntax_err(table, position, "expected differently");
	}
	return;
}

void match_by_class(ast* tree, node_array* arr, symbol_table* table, node_type_class type, long* position)
{
	printf("Matching %s at position nr %ld\n", node_type_get_class(type), *position);
	if (node_array_get_node_type_class(arr, *position) == type) {
		ast_add(tree, ast_make());
		ast_set_node(ast_get_last(tree), node_array_get_node(arr, *position));
		(*position)++;
	} else {
		parse_syntax_err(table, position, "expected differently");
	}
	return;
}

void match_by_class_no_append(ast* tree, node_array* arr, symbol_table* table, node_type_class type, long* position)
{
	printf("Matching %s at position nr %ld\n", node_type_get_class(type), *position);
	if (node_array_get_node_type_class(arr, *position) == type) {
		(*position)++;
	} else {
		parse_syntax_err(table, position, "expected differently");
	}
	return;
}
