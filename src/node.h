#ifndef NODE_H
#define NODE_H
#define NODE_ARRAY_INIT_SIZE 10
#include <stdlib.h>
typedef enum{
	assignment_token = 127,

	selector_token = 128,
	semicolon_token = 130,
	colon_token = 131,

	comma_token = 133,
	
	directive_token = 132,
	program_directive_token,
	module_directive_token,
	include_directive_token,
	macro_directive_token,

	plus_operator_token = 108,
	minus_operator_token = 103,
	multiplication_operator_token = 113,
	division_operator_token = 116,
	mod_operator_token = 129,
	pot_operator_token = 115,
	floor_div_operator_token = 118,

	imm_plus_operator_token = 106,
	imm_minus_operator_token = 102,
	imm_mul_operator_token = 114,
	imm_division_operator_token = 117,
	decrement_operator_token = 104,
	increment_operator_token = 107,

	gt_operator_token = 109,
	lt_operator_token = 111,
	le_operator_token = 112,
	ge_operator_token = 110,

	identifier_token = 100,

	opening_bracket_token = 121,
	closing_bracket_token = 122,

	opening_s_bracket_token = 126,
	closing_s_bracket_token = 125,

	opening_c_bracket_token = 123,
	closing_c_bracket_token = 124,

	string_type_token = 119,
	char_type_token = 120,
	int_type_token = 105,
	float_type_token = 101,

	string_type_type_token,
	char_type_type_token,
	int_type_type_token,
	float_type_type_token,

	return_keyword_token,
	for_keyword_token,
	while_keyword_token,
	if_keyword_token,
	else_keyword_token,
	elif_keyword_token,

	program_n
} node_type;

typedef struct {
	node_type type;
	long value;
} node;

typedef struct {
	node *node_array;
	long used;
	long size;
} node_array;

node_array *node_array_make();
void node_array_add(node_array *arr, node_type type, long value);

node_type node_array_get_node_type(node_array *arr, long position);

node *node_array_get_node(node_array *arr, long position);

node *node_make(node_type type, long value);

#endif
