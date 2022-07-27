#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "node.h"
#include "scanner.h"
#include "symbol_table.h"
#include "typetable.h"

typedef struct parser_result {
	ast *tree;
	symbol_table *table;
	typetable *type_table;
} parser_result;

parser_result parse_program(scanner_result res);

void parse_syntax_err(symbol_table *table, size_t *position, char *err);

void program(ast *tree, node_array *arr, symbol_table *table, size_t *position);

void parameter_list(ast *tree, node_array *arr, symbol_table *table,
					size_t *position);

void function(ast *tree, node_array *arr, symbol_table *table,
			  size_t *position);

void program_directive(ast *tree, node_array *arr, symbol_table *table,
					   size_t *position);

void secondary_directive_list(ast *tree, node_array *arr, symbol_table *table,
							  size_t *position);

void match(ast *tree, node_array *arr, symbol_table *table, node_type type,
		   size_t *position);

void match_no_append(ast *tree, node_array *arr, symbol_table *table,
					 node_type type, size_t *position);

void type(ast *tree, node_array *arr, symbol_table *table, size_t *position);

void functions(ast *tree, node_array *arr, symbol_table *table,
			   size_t *position);

void match_by_class(ast *tree, node_array *arr, symbol_table *table,
					node_type_class type, size_t *position);

void match_by_class_no_append(ast *tree, node_array *arr, symbol_table *table,
							  node_type_class type, size_t *position);

void include_directive_select(ast *tree, node_array *arr, symbol_table *table,
							  size_t *position);

void var(ast *tree, node_array *arr, symbol_table *table, size_t *position);

void print_tree(ast *tree, int depth);

void declaration(ast *tree, node_array *arr, symbol_table *table,
				 size_t *position);

void factor(ast *tree, node_array *arr, symbol_table *table, size_t *position);
void expression(ast *tree, node_array *arr, symbol_table *table,
				size_t *position);
void simple_expression(ast *tree, node_array *arr, symbol_table *table,
					   size_t *position);

void block(ast *tree, node_array *arr, symbol_table *table, size_t *position);

void argument_list(ast *tree, node_array *arr, symbol_table *table,
				   size_t *position);

void term(ast *tree, node_array *arr, symbol_table *table, size_t *position);
void fun_call(ast *tree, node_array *arr, symbol_table *table,
			  size_t *position);

void return_statement(ast *tree, node_array *arr, symbol_table *table,
					  size_t *position);

void for_statement(ast *tree, node_array *arr, symbol_table *table,
				   size_t *position);

void secondary_directives(ast *tree, node_array *arr, symbol_table *table,
						  size_t *position);

#endif
