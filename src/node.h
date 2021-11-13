#ifndef NODE_H
#define NODE_H
#define NODE_ARRAY_INIT_SIZE 10
#include <stdlib.h>
typedef enum{
	identifier_token,


	assignment_token,
	imm_minus_operator_token,
	imm_plus_operator_token,
	imm_mul_operator_token,
	imm_division_operator_token,

	selector_token,
	semicolon_token,
	colon_token,
	comma_token,

	// DIRECTIVES
	program_directive_token,
	module_directive_token,
	include_directive_token,
	macro_directive_token,

	// BINARY OPERATORS
	plus_operator_token,
	minus_operator_token,
	multiplication_operator_token,
	division_operator_token,
	mod_operator_token,
	pot_operator_token,
	gt_operator_token,
	lt_operator_token,
	le_operator_token,
	ge_operator_token,
	floor_div_operator_token,
	
	// UNARY OPERATORS
	increment_operator_token,
	not_token,
	decrement_operator_token,

	// STRUCTURE //
	opening_bracket_token,
	closing_bracket_token,

	opening_s_bracket_token,
	closing_s_bracket_token,

	opening_c_bracket_token,
	closing_c_bracket_token,

	// Literals
	string_literal,
	char_literal,
	int_literal,
	float_literal,

	// types
	string_type_token,
	char_type_token,
	int_type_token,
	float_type_token,

	// Control flow
	return_keyword_token,
	for_keyword_token,
	while_keyword_token,
	if_keyword_token,
	else_keyword_token,
	elif_keyword_token,
	function_token,

	// Ntm
	if_statement_n,
	expression_n,
	factor_n,
	term_n,
	program_n,
	declaration_n,
	functioncall_n,
	argument_n,
	argument_list_n,
	block_n,
	var_n,
	module_n,
	secondarydirective_n,
	secondarydirective_list_n,
	include_directive_n,
	include_directive_subselect_n,
	program_directive_n,
	module_directive_n,
	macro_directive_n,
	function_n,
	functions_n,
	unop_n,
	binop_n,
	parameter_n,
	parameter_list_n,
	type_n

} node_type;

typedef enum {
	unop_c,
	binop_c,
	assign_c,
	sec_directive_c,
	prim_directive_c,
	literal_c,
	type_c,
	nont_c,
	keyword_c,
	nac_c,
	bracket_c,
	punctuation_c,
	directive_c
	
} node_type_class;

typedef struct {
	node_type type;
	node_type_class type_class;
	long value;
} node;

typedef struct {
	node *node_array;
	long used;
	long size;
} node_array;

node_array *node_array_make();
void node_array_add(node_array *arr, node_type type, node_type_class type_class, long value);

node_type node_array_get_node_type(node_array *arr, long position);
node_type_class node_array_get_node_type_class(node_array *arr, long position);

node *node_array_get_node(node_array *arr, long position);

long *node_array_get_val(node_array *arr, long position);
node *node_make(node_type type, node_type_class type_class, long value);

char *node_type_get_canonial(node_type type);

char *node_type_get_class(node_type_class type );

#endif
