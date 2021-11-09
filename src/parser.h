#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "scanner.h"

ast *parse_program(scanner_result res);

void parse_syntax_err(long line);

void program(ast *tree, node_array *arr, symbol_table *table, long *lookahead);

void parameter_list(ast *tree, node_array *arr, symbol_table *table, long *lookahead);

void function(ast *tree, node_array *arr, symbol_table *table, long *lookahead);

void program_directive(ast *tree, node_array *arr, symbol_table *table, long *lookahead);

void secondary_directive_list(ast *tree, node_array *arr, symbol_table *table, long *lookahead);

void match(node_array *arr, symbol_table *table, node_type type, long *lookahead);

void type(ast *tree, node_array *arr, symbol_table *table, long *lookahead);

#endif
