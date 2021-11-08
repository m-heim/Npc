#ifndef TOKEN_H
#define TOKEN_H
#define TOKEN_ARRAY_INIT_SIZE 10
#include <stdlib.h>
typedef enum{
	assignment_token = 127,

	selector_token = 128,
	semicolon_token = 130,
	colon_token = 131,

	comma_token = 133,
	
	directive_token = 132,

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

	return_keyword_token,
	for_keyword_token,
	while_keyword_token,
	if_keyword_token,
	else_keyword_token,
	elif_keyword_token
} token_type;

typedef struct {
	token_type type;
	long value;
} token;

typedef struct {
	token *tkn_array;
	size_t used;
	size_t size;
} token_array;

token_array *token_array_make();
void token_array_add(token_array *arr, token_type type, long value);

token_type token_array_get_token_type(token_array *arr, long position)

token *token_array_get_token(token_array *arr, long position);

token *token_make(token_type type, long value);

#endif
