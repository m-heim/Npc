#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "node.h"
#include "scanner.h"
#include "symbol_table.h"
#include "typetable.h"

typedef struct parser_result {
	ast* tree;
	symbol_table* table;
	typetable* type_table;
} parser_result;

parser_result parse_program(scanner_result res);

void parse_syntax_err(symbol_table* table, long* lookahead, char* err);

void program(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void parameter_list(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void function(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void program_directive(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void secondary_directive_list(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void match(ast* tree, node_array* arr, symbol_table* table, node_type type, long* lookahead);

void match_no_append(ast* tree, node_array* arr, symbol_table* table, node_type type, long* lookahead);

void type(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void functions(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void match_by_class(ast* tree, node_array* arr, symbol_table* table, node_type_class type, long* lookahead);

void match_by_class_no_append(ast* tree, node_array* arr, symbol_table* table, node_type_class type, long* lookahead);

void include_directive_select(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void var(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void print_tree(ast* tree, int depth);

void declaration(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void factor(ast* tree, node_array* arr, symbol_table* table, long* lookahead);
void expression(ast* tree, node_array* arr, symbol_table* table, long* lookahead);
void simple_expression(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void block(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void argument_list(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void term(ast* tree, node_array* arr, symbol_table* table, long* lookahead);
void fun_call(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void return_statement(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void for_statement(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

void secondary_directives(ast* tree, node_array* arr, symbol_table* table, long* lookahead);

#endif
