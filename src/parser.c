#include "parser.h"
#include "ast.h"
#include "log.h"
#include "scanner.h"
#include "symbol_table.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>

parser_result *parser_result_make(ast *tree, symbol_table *table,
								  typetable *type_table) {
	parser_result *res = malloc(sizeof(parser_result));
	res->type_table = type_table;
	res->table = table;
	res->tree = tree;
	return res;
}
parser *parser_make(ast *tree, symbol_table *table, int debug,
					token_array *arr) {
	parser *p = malloc(sizeof(parser));
	p->debug = debug;
	p->tree = tree;
	p->arr = arr;
	p->table = table;
	p->position = 0;
	return p;
}

parser_result *parse_program(scanner_result res, int debug) {
	typetable *type_table = typetable_make();
	parser *parser = parser_make(ast_make(), res.table, debug, res.token_array);
	npc_debug_log(debug, "{Parse} - Parsing program now.");
	program(parser);
	npc_debug_log(debug, "{Parse} - Done parsing program.");
	parser->tree = ast_get_root(parser->tree);
	if (debug) {
		print_tree(parser->tree, 0);
	}
	return parser_result_make(parser->tree, res.table,type_table);
}

void parse_syntax_err(parser *parser, char *err) {
	printf("ERROR: line %ld on token %s\n",
		   symbol_table_get_line(parser->table, parser->position),
		   symbol_table_get_value(parser->table, parser->position));
	_Exit(1);
}

void program(parser *parser) {
	if (parser->debug) {
		printf("Parsing PROGRAM now\n");
	}
	// set top token
	ast_set_token(parser->tree, token_make(program_n, nont_c, -1));
	// match program directive
	program_directive(parser);
	// option
	if (token_array_get_token_type_class(parser->arr, parser->position) ==
		sec_directive_c) {
		secondary_directive_list(parser);
	}

	functions(parser);
	match_no_append(parser, end_directive_token);
}

void function(parser *parser) {
	if (parser->debug) {
		printf("Parsing FUNCTION\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(function_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	type(parser);
	match(parser, identifier_token);
	match_no_append(parser, opening_bracket_token);

	if (token_array_get_token_type(parser->arr, parser->position) ==
		closing_bracket_token) {
		match_no_append(parser, closing_bracket_token);
	} else {
		parameter_list(parser);
		match_no_append(parser, closing_bracket_token);
	}
	block(parser);

	parser->tree = ast_get_parent(parser->tree);
}

void type(parser *parser) {
	if (parser->debug) {
		printf("Parsing TYPES\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree), token_make(type_n, type_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match_by_class(parser, type_c);
	if (token_array_get_token_type(parser->arr, parser->position) ==
		opening_s_bracket_token) {
		while (token_array_get_token_type(parser->arr, parser->position) ==
			   opening_s_bracket_token) {
			match_no_append(parser, opening_s_bracket_token);
			if (token_array_get_token_type(parser->arr, parser->position) ==
				int_literal_token) {
				match(parser, int_literal_token);
			}

			match_no_append(parser, closing_s_bracket_token);
		}
	}
	parser->tree = ast_get_parent(parser->tree);
}

// Parses multiple functions, but at least one.
void functions(parser *parser) {
	if (parser->debug) {
		printf("Parsing FUNCTIONS\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(functions_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);
	do {
		function(parser);
	} while (token_array_get_token_type_class(parser->arr, parser->position) ==
			 type_c);
	parser->tree = ast_get_parent(parser->tree);
}

void parameter(parser *parser) {
	if (parser->debug) {
		printf("Parsing PARAM\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(parameter_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	type(parser);

	match(parser, identifier_token);
	parser->tree = ast_get_parent(parser->tree);
}

void parameter_list(parser *parser) {
	if (parser->debug) {
		printf("Parsing PARAMETER LIST\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(parameter_list_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);
	parameter(parser);
	while (token_array_get_token_type(parser->arr, parser->position) ==
		   comma_token) {
		match_no_append(parser, comma_token);
		parameter(parser);
	}
	parser->tree = ast_get_parent(parser->tree);
}

void unop(parser *parser) {
	if (parser->debug) {
		printf("Parsing UNOP\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree), token_make(unop_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match_by_class(parser, unop_c);
	parser->tree = ast_get_parent(parser->tree);
}

void binop(parser *parser) {
	if (parser->debug) {
		printf("Parsing BINOP\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree), token_make(binop_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match_by_class(parser, binop_c);
	parser->tree = ast_get_parent(parser->tree);
}

void program_directive(parser *parser) {
	if (parser->debug) {
		printf("Parsing PROGRAM DIRECTIVE\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(program_directive_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match_no_append(parser, program_directive_token);
	match(parser, identifier_token);
	if (parser->debug) {
		printf("done Parsing PROGRAM DIRECTIVE\n");
	}
	parser->tree = ast_get_parent(parser->tree);
}

void module_directive(parser *parser) {
	if (parser->debug) {
		printf("Parsing MODULE DIRECTIVE\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(module_directive_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match_no_append(parser, module_directive_token);
	match(parser, identifier_token);
	parser->tree = ast_get_parent(parser->tree);
}

void include_directive(parser *parser) {
	if (parser->debug) {
		printf("Parsing INC DIRECTIVE\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(include_directive_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match_no_append(parser, include_directive_token);
	include_directive_select(parser);
	parser->tree = ast_get_parent(parser->tree);
}

void if_statement(parser *parser) {
	if (parser->debug) {
		printf("Parsing IF\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(if_statement_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match_no_append(parser, if_keyword_token);
	match_no_append(parser, opening_bracket_token);

	expression(parser);

	match_no_append(parser, closing_bracket_token);

	block(parser);
	parser->tree = ast_get_parent(parser->tree);
	if (parser->debug) {
		printf("Parsing IF done\n");
	}
}

void return_statement(parser *parser) {
	if (parser->debug) {
		printf("Parsing return statement\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(return_statement_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match_no_append(parser, return_keyword_token);
	// should also be able to return statement?
	expression(parser);
	match_no_append(parser, semicolon_token);

	parser->tree = ast_get_parent(parser->tree);
	if (parser->debug) {
		printf("Parsing return statement done\n");
	}
}

void for_statement(parser *parser) {
	if (parser->debug) {
		printf("Parsing for statement\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(for_statement_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match_no_append(parser, for_keyword_token);
	// should also be able to return statement?

	match_no_append(parser, opening_bracket_token);
	declaration(parser);
	match_no_append(parser, semicolon_token);
	expression(parser);
	match_no_append(parser, semicolon_token);
	expression(parser);
	match_no_append(parser, closing_bracket_token);

	block(parser);

	parser->tree = ast_get_parent(parser->tree);
	if (parser->debug) {
		printf("Parsing for statement done\n");
	}
}

void assignment(parser *parser) {
	if (parser->debug) {
		printf("Parsing Assignment\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(if_statement_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	var(parser);

	match_by_class(parser, assign_c);

	expression(parser);
	match_no_append(parser, semicolon_token);
	parser->tree = ast_get_parent(parser->tree);
}

void statement(parser *parser) {
	if (parser->debug) {
		printf("Parsing Statement\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(statement_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	if (token_array_get_token_type(parser->arr, parser->position) ==
		if_keyword_token) {
		if_statement(parser);
	} else if (token_array_get_token_type_class(parser->arr,
												parser->position) == type_c) {
		declaration(parser);
	} else if (token_array_get_token_type(parser->arr, parser->position) ==
			   for_keyword_token) {
		for_statement(parser);
	} else if (token_array_get_token_type(parser->arr, parser->position) ==
			   identifier_token) {
		if (token_array_get_token_type(parser->arr, parser->position + 1) ==
			opening_bracket_token) {
			fun_call(parser);
		} else if (token_array_get_token_type_class(
					   parser->arr, parser->position + 1) == assign_c) {
			assignment(parser);
		} else {
			parse_syntax_err(parser, "Expected Function call or assignment");
		}
	} else if (token_array_get_token_type(parser->arr, parser->position) ==
			   return_keyword_token) {
		return_statement(parser);
	}
	parser->tree = ast_get_parent(parser->tree);
}

void simple_expression(parser *parser) {
	if (parser->debug) {
		printf("Parsing simple exp\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(simple_expression_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	term(parser);

	if (token_array_get_token_type(parser->arr, parser->position) ==
		plus_operator_token) {
		match(parser, plus_operator_token);
		simple_expression(parser);
	} else if (token_array_get_token_type(parser->arr, parser->position) ==
			   minus_operator_token) {
		match(parser, minus_operator_token);
		simple_expression(parser);
	}
	parser->tree = ast_get_parent(parser->tree);
}

void expression(parser *parser) {
	if (parser->debug) {
		printf("Parsing Exp\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(expression_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	simple_expression(parser);

	if (token_array_get_token_type_class(parser->arr, parser->position) ==
		relop_c) {
		match_by_class(parser, relop_c);
		simple_expression(parser);
	}
	parser->tree = ast_get_parent(parser->tree);
}

void term(parser *parser) {
	if (parser->debug) {
		printf("Parsing terms\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree), token_make(term_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	factor(parser);

	if (token_array_get_token_type(parser->arr, parser->position) ==
		multiplication_operator_token) {
		match(parser, multiplication_operator_token);
		term(parser);
	} else if (token_array_get_token_type(parser->arr, parser->position) ==
			   division_operator_token) {
		match(parser, division_operator_token);
		term(parser);
	}
	parser->tree = ast_get_parent(parser->tree);
}

void var(parser *parser) {
	if (parser->debug) {
		printf("Parsing var\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(if_statement_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match(parser, identifier_token);
	if (token_array_get_token_type(parser->arr, parser->position) ==
		opening_s_bracket_token) {
		match_no_append(parser, opening_s_bracket_token);
		expression(parser);
		match_no_append(parser, closing_s_bracket_token);
	}
	parser->tree = ast_get_parent(parser->tree);
}

void declaration(parser *parser) {
	if (parser->debug) {
		printf("Parsing Decl\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(declaration_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	type(parser);
	match(parser, identifier_token);
	if (token_array_get_token_type(parser->arr, parser->position) ==
		assignment_token) {
		match_no_append(parser, assignment_token);
		expression(parser);
		match(parser, semicolon_token);
	} else {
		parse_syntax_err(parser, "expected assignment token");
	}
	parser->tree = ast_get_parent(parser->tree);
}

void fun_call(parser *parser) {
	if (parser->debug) {
		printf("Parsing Functioncall\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(function_call_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match(parser, identifier_token);

	match_no_append(parser, opening_bracket_token);

	if (token_array_get_token_type(parser->arr, parser->position) !=
		closing_bracket_token) {
		argument_list(parser);
	}
	match_no_append(parser, closing_bracket_token);
	parser->tree = ast_get_parent(parser->tree);
	npc_debug_log(parser->debug, "Parsing function call done");
}

void argument(parser *parser) {
	if (parser->debug) {
		printf("Parsing Argument\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(argument_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	expression(parser);
	parser->tree = ast_get_parent(parser->tree);
}

void argument_list(parser *parser) {
	if (parser->debug) {
		printf("Parsing Argumentlist\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(argument_list_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);
	token_type next = token_array_get_token_type(parser->arr, parser->position);

	do {
		argument(parser);
		next = token_array_get_token_type(parser->arr, parser->position);
		if (next == comma_token) {
			match_no_append(parser, comma_token);
		}
	} while (next == comma_token);
	parser->tree = ast_get_parent(parser->tree);
}

void factor(parser *parser) {
	if (parser->debug) {
		printf("Parsing Factor\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree), token_make(factor_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	switch (token_array_get_token_type(parser->arr, parser->position)) {
	case not_token:
		break;
	case increment_operator_token:
		break;
	case decrement_operator_token:
		break;
	case opening_bracket_token:
		match_no_append(parser, opening_bracket_token);
		expression(parser);
		match_no_append(parser, closing_bracket_token);
		break;
	case identifier_token:
		if (token_array_get_token_type(parser->arr, parser->position + 1) ==
			opening_bracket_token) {
			fun_call(parser);
		} else if (token_array_get_token_type(parser->arr,
											  parser->position + 1) ==
				   increment_operator_token) {
			var(parser);
			match(parser, increment_operator_token);
		} else if (token_array_get_token_type(parser->arr,
											  parser->position + 1) ==
				   decrement_operator_token) {
			var(parser);
			match(parser, decrement_operator_token);
		} else {
			var(parser);
		}
		break;
	case float_literal_token:
		match(parser, float_literal_token);
		break;
	case string_literal_token:
		match(parser, string_literal_token);
		break;
	case int_literal_token:
		match(parser, int_literal_token);
		break;
	case char_literal_token:
		match(parser, char_literal_token);
		break;

	default:
		break;
	}
	parser->tree = ast_get_parent(parser->tree);
}

void block(parser *parser) {
	if (parser->debug) {
		printf("Parsing block\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree), token_make(block_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	match_no_append(parser, opening_c_bracket_token);

	while (token_array_get_token_type(parser->arr, parser->position) !=
		   closing_c_bracket_token) {
		statement(parser);
	}

	match_no_append(parser, closing_c_bracket_token);
	parser->tree = ast_get_parent(parser->tree);
	if (parser->debug) {
		printf("Parsing block done.\n");
	}
}

void include_directive_select(parser *parser) {
	if (parser->debug) {
		printf("Parsing DIR SELECTT\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(include_directive_subselect_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);
	do {
		match(parser, identifier_token);
		if (token_array_get_token_type(parser->arr, parser->position) ==
			selector_token) {
			match_no_append(parser, selector_token);
		}
		// maybe change this
	} while (token_array_get_token_type(parser->arr, parser->position) ==
			 identifier_token);

	parser->tree = ast_get_parent(parser->tree);
	if (parser->debug) {
		printf("Parsing DIR SELECTT done.\n");
	}
}

void secondary_directives(parser *parser) {
	if (parser->debug) {
		printf("Parsing SEC DIR\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(secondarydirective_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	switch (token_array_get_token_type(parser->arr, parser->position)) {
	case include_directive_token:
		include_directive(parser);
		break;
	case macro_directive_token:
		// implement
		break;
	default:
		_Exit(1);
	}
	parser->tree = ast_get_parent(parser->tree);
}

void secondary_directive_list(parser *parser) {
	if (parser->debug) {
		printf("Parsing SEC DIR LIST\n");
	}
	ast_add(parser->tree, ast_make());
	ast_set_token(ast_get_last(parser->tree),
				  token_make(secondarydirective_list_n, nont_c, -1));

	parser->tree = ast_get_last(parser->tree);

	do {
		secondary_directives(parser);
	} while (token_array_get_token_type_class(parser->arr, parser->position) ==
			 sec_directive_c);
	parser->tree = ast_get_parent(parser->tree);
}

void print_tree(ast *tree, int depth) {
	for (int i = 0; i < depth; i++) {
		printf("  ");
	}
	printf("> %s\n", token_type_get_canonial(tree->n.type));
	for (int i = 0; i < tree->used; i++) {
		print_tree(tree->children[i], depth + 1);
	}
}

void match(parser *parser, token_type type) {
	if (parser->debug) {
		printf("Matching %s at %ld, got %s\n", token_type_get_canonial(type),
			   parser->position, token_type_get_canonial(token_array_get_token_type(parser->arr, parser->position)));
	}
	if (token_array_get_token_type(parser->arr, parser->position) == type) {
		ast_append(parser->tree,
				   token_array_get_token(parser->arr, parser->position));
		parser->position++;
	} else {
		parse_syntax_err(parser, "expected differently in match");
	}
	return;
}

void match_no_append(parser *parser, token_type type) {
	if (parser->debug) {
		printf("Matching %s at %ld, got %s\n", token_type_get_canonial(type),
			   parser->position, token_type_get_canonial(token_array_get_token_type(parser->arr, parser->position)));
	}
	if (token_array_get_token_type(parser->arr, parser->position) == type) {
		parser->position++;
	} else {
		parse_syntax_err(parser, "expected differently in match non append");
	}
	return;
}

void match_by_class(parser *parser, token_type_class type) {
	if (parser->debug) {
		printf("Matching %s at %ld, got %s\n", token_type_get_class(type),
			   parser->position, token_type_get_class(token_array_get_token_type_class(parser->arr, parser->position)));
	}
	if (token_array_get_token_type_class(parser->arr, parser->position) ==
		type) {
		ast_append(parser->tree,
				   token_array_get_token(parser->arr, parser->position));
		parser->position++;
	} else {
		parse_syntax_err(parser, "expected differently in match by class");
	}
	return;
}

void match_by_class_no_append(parser *parser, token_type_class type) {
	if (parser->debug) {
		printf("Matching %s at %ld, got %s\n", token_type_get_class(type),
			   parser->position, token_type_get_class(token_array_get_token_type_class(parser->arr, parser->position)));
	}
	if (token_array_get_token_type_class(parser->arr, parser->position) ==
		type) {
		parser->position++;
	} else {
		parse_syntax_err(parser,
						 "expected differently in match by class non append");
	}
	return;
}
