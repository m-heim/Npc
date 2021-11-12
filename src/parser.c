#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "node.h"
#include "parser.h"
#include "scanner.h"
#include "symbol_table.h"

int parser_debug = 1;

ast *parse_program(scanner_result res) {
	long l = 0;
	long *lookahead = &l;
	ast *tree = ast_make();
	program(tree, res.node_array, res.table, lookahead);
	return tree;
}

void parse_syntax_err(long line) {
	printf("ERROR: line %ld\n", line);
	_Exit(1);
}

void program(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
		if (parser_debug) {
		printf("Parsing PROGRAM now\n");
	}
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
		if (parser_debug) {
		printf("Parsing FUNCTION\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(function_n, nont_c ,-1));

	tree = ast_get_last(tree);

	type(tree, arr, table, lookahead);
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

void type(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing TYPES\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(type_n, type_c, -1));

	tree = ast_get_last(tree);

	match_by_class(tree, arr, table, type_c, lookahead);
	if(node_array_get_node_type(arr, *lookahead) == opening_s_bracket_token) {
		while(node_array_get_node_type(arr, *lookahead) == opening_s_bracket_token) {
			match(tree, arr, table, opening_s_bracket_token, lookahead);
			match(tree, arr, table, int_literal, lookahead);
			match(tree, arr, table, closing_s_bracket_token, lookahead);
		}
	}

}


// Parses multiple functions, but at least one.
void functions(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing FUNCTIONS\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(functions_n, nont_c, -1));

	tree = ast_get_last(tree);
	if (node_array_get_node_type_class(arr, *lookahead) == type_c) {
		while (node_array_get_node_type_class(arr, *lookahead) == type_c) {
			function(tree, arr, table, lookahead);
		}
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
	return;
}

void parameter(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing PARAM\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(parameter_n, nont_c, -1));

	tree = ast_get_last(tree);

	type(tree, arr, table, lookahead);

	match(tree, arr, table, identifier_token, lookahead);
	return;
}

void parameter_list(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing PARAMETER LIST\n");
	}
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

void unop(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing UNOP\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(unop_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_by_class(tree, arr, table, unop_c, lookahead);
}

void binop(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing BINOP\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(binop_n, nont_c, -1));

	tree = ast_get_last(tree);

	match_by_class(tree, arr, table, binop_c, lookahead);
}

void program_directive(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing PROGRAM DIRECTIVE\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(program_directive_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	match(tree, arr, table, program_directive_token, lookahead);
	match(tree, arr, table, identifier_token, lookahead);
	match(tree, arr, table, semicolon_token, lookahead);
	return;
}

void module_directive(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing MODULE DIRECTIVE\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(module_directive_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	match(tree, arr, table, module_directive_token, lookahead);
	match(tree, arr, table, identifier_token, lookahead);
	match(tree, arr, table, semicolon_token, lookahead);
}

void include_directive(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing INC DIRECTIVE\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(include_directive_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	match(tree, arr, table, include_directive_token, lookahead);
	include_directive_select(tree, arr, table, lookahead);
	match(tree, arr, table, semicolon_token, lookahead);
}


void if_statement(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing IF\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(if_statement_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	match(tree, arr, table, if_keyword_token, lookahead);
	match(tree, arr, table, opening_bracket_token, lookahead);

	expression(tree, arr, table, lookahead);
	
	match(tree, arr, table, closing_bracket_token, lookahead);
	match(tree, arr, table, opening_c_bracket_token, lookahead);

	block(tree, arr, table, lookahead);
}

void expression(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {

}

void term(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {

}

void var(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing var\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(if_statement_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	match(tree, arr, table, identifier_token, lookahead);
	if(node_array_get_node_type(arr, *lookahead) == opening_s_bracket_token) {
		match(tree, arr, table, opening_s_bracket_token, lookahead);
		expression(tree, arr, table, lookahead);
		match(tree, arr, table, closing_s_bracket_token, lookahead);
	}
}

void declaration(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing Decl\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(declaration_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	type(tree, arr, table, lookahead);
	match(tree, arr, table, identifier_token, lookahead);

	match(tree, arr, table, assignment_token, lookahead);

	expression(tree, arr, table, lookahead);
}

void fun_call(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
		if (parser_debug) {
		printf("Parsing Functioncall\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(declaration_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	match(tree, arr, table, identifier_token, lookahead);

	match(tree, arr, table, opening_bracket_token, lookahead);

	if (node_array_get_node_type(arr, *lookahead) != opening_bracket_token) {
		argument_list(tree, arr, table, lookahead);
	}
	match(tree, arr, table, closing_bracket_token, lookahead);
}

void argument(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing Argument\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(argument_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	expression(tree, arr, table, lookahead);
}

void argument_list(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
		if (parser_debug) {
		printf("Parsing Argumentlist\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(argument_list_n, nont_c, -1));
	
	tree = ast_get_last(tree);
	node_type t = node_array_get_node_type(arr, *lookahead);
	if (t == increment_operator_token || t == decrement_operator_token || t == not_token || t == identifier_token || t == opening_bracket_token || t == float_literal || t == string_literal || t == char_literal || t == int_literal) {
		t = node_array_get_node_type(arr, *lookahead);
		argument(tree, arr, table, lookahead);
		while (node_array_get_node_type(arr, *lookahead) == comma_token) {
			match(tree, arr, table, comma_token, lookahead);
			argument(tree, arr, table, lookahead);
		}
	}
}


void factor(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing Factor\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(factor_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	switch(node_array_get_node_type(arr, *lookahead)) {
		case not_token:
		
		case increment_operator_token:

		case decrement_operator_token:

		case opening_bracket_token:

		case identifier_token:
			if (node_array_get_node_type(arr, *lookahead + 1) == opening_bracket_token) {

			} else {
				var(tree, arr, table, lookahead);
			}
		case float_literal:

		case string_literal:

		case int_literal:

		case char_literal:

		default:
	}
	
	if (node_array_get_node_type(arr, *lookahead) == not_token) {

	} else if (node_array_get_node_type(arr, *lookahead) == increment_operator_token) {

	} else if (node_array_get_node_type(arr, *lookahead) == decrement_operator_token) {

	} else if (node_array_get_node_type(arr, *lookahead) == opening_bracket_token) {

	} else if (node_array_get_node_type(arr, *lookahead) == identifier_token) {

	}
}

void block(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {

}


void include_directive_select(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing DIR SELECTT\n");
	}
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

void secondary_directives(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing SEC DIR\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(secondarydirective_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	printf("1\n");
	if (node_array_get_node_type_class(arr, *lookahead) == sec_directive_c) {
		printf("1\n");
		printf("1\n");
		if (node_array_get_node_type(arr, *lookahead) == include_directive_token) {
			include_directive(tree, arr, table, &*lookahead);
		} else if (node_array_get_node_type(arr, *lookahead) == macro_directive_token) {
			//implement
		} else {
			parse_syntax_err(symbol_table_get_line(table, *lookahead));
		}
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
}

void secondary_directive_list(ast *tree, node_array *arr, symbol_table *table, long *lookahead) {
	if (parser_debug) {
		printf("Parsing SEC DIR LIST\n");
	}
	ast_add(tree, ast_make());
	ast_set_node(ast_get_last(tree), node_make(secondarydirective_list_n, nont_c, -1));
	
	tree = ast_get_last(tree);

	if (node_array_get_node_type_class(arr, *lookahead) == sec_directive_c) {
		while (node_array_get_node_type_class(arr, *lookahead) == sec_directive_c) {
			secondary_directives(tree, arr, table, lookahead);
		}
	}
}

void print_tree(ast *tree, int depth) {
	int i;
	for(i = 0; i < depth; i++) {
		printf("  ");
	}
	printf("> %s\n", node_type_get_canonial(tree->n.type));
	for(i = 0; i < tree->used; i++) {
		print_tree(tree->children[i], depth + 1);
	}
}


void match(ast *tree, node_array *arr, symbol_table *table, node_type type, long *lookahead) {
	printf("Matching %s at %ld\n", node_type_get_canonial(type), *lookahead);
	if (node_array_get_node_type(arr, *lookahead) == type) {
		ast_add(tree, ast_make());
		ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
		(*lookahead)++;
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
	return;
}

void match_by_class(ast *tree, node_array *arr, symbol_table *table, node_type_class type, long *lookahead) {
	printf("Matching %d at position nr %ld\n", type, *lookahead);
	if (node_array_get_node_type_class(arr, *lookahead) == type) {
		ast_add(tree, ast_make());
		ast_set_node(ast_get_last(tree), node_array_get_node(arr, *lookahead));
		(*lookahead)++;
	} else {
		parse_syntax_err(symbol_table_get_line(table, *lookahead));
	}
	return;
}
