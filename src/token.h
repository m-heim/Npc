#ifndef TOKEN_H
#define TOKEN_H
#define TOKEN_ARRAY_INIT_SIZE 10
#include <stdlib.h>
typedef enum{
	assignment = 127,

	selector = 128,
	semicolon = 130,
	colon = 131,

	comma = 133,
	
	directive = 132,

	plus_operator = 108,
	minus_operator = 103,
	multiplication_operator = 113,
	division_operator = 116,
	mod_operator = 129,
	pot_operator = 115,
	floor_div_operator = 118,

	imm_plus_operator = 106,
	imm_minus_operator = 102,
	imm_mul_operator = 114,
	imm_division_operator = 117,
	decrement_operator = 104,
	increment_operator = 107,

	gt_operator = 109,
	lt_operator = 111,
	le_operator = 112,
	ge_operator = 110,

	identifier = 100,

	opening_bracket = 121,
	closing_bracket = 122,

	opening_s_bracket = 126,
	closing_s_bracket = 125,

	opening_c_bracket = 123,
	closing_c_bracket = 124,

	string_type = 119,
	char_type = 120,
	int_type = 105,
	float_type = 101,

	return_keyword,
	for_keyword,
	while_keyword,
	if_keyword,
	else_keyword,
	elif_keyword
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

token *token_make(token_type type, long value);

#endif
