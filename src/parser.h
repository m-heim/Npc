#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "scanner.h"
#include "symbol_table.h"
#include "token.h"
#include "typetable.h"

typedef struct parser_result {
	ast *tree;
	symbol_table *table;
	typetable *type_table;
} parser_result;

typedef struct parser {
	ast *tree;
	symbol_table *table;
	token_array *arr;
	size_t position;
	int debug;
} parser;

parser_result *parse_program(scanner_result res, int debug);

parser_result *parser_result_make(ast *tree, symbol_table *table,
								  typetable *type_table);

parser *parser_make(ast *tree, symbol_table *table, int debug,
					token_array *arr);

void parse_syntax_err(parser *parser, char *err);

void program(parser *parser);

void parameter_list(parser *parser);

void function(parser *parser);

void program_directive(parser *parser);

void secondary_directive_list(parser *parser);

void match(parser *parser, token_type type);

void match_no_append(parser *parser, token_type type);

void type(parser *parser);

void functions(parser *parser);

void match_by_class(parser *parser, token_type_class type);

void match_by_class_no_append(parser *parser, token_type_class type);

void include_directive_select(parser *parser);

void include_directive(parser *parser);

void var(parser *parser);

void jump_statement(parser *parser);

void assignment(parser *parser);

void print_tree(ast *tree, int depth);

void declaration(parser *parser);

void factor(parser *parser);

void expression(parser *parser);

void simple_expression(parser *parser);

void block(parser *parser);

void argument_list(parser *parser);

void term(parser *parser);

void fun_call(parser *parser);

void return_statement(parser *parser);

void for_statement(parser *parser);

void secondary_directives(parser *parser);

#endif
