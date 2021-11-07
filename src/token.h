#ifndef TOKEN_H
#define TOKEN_H
#define TOKEN_ARRAY_INIT_SIZE 10
#include <stdlib.h>
typedef enum{
	assignment,

	selector,
	semicolon,
	colon,

	plus_operator,
	minus_operator,
	multiplication_operator,
	division_operator,
	mod_operator,
	pot_operator,
	floor_div_operator,

	imm_plus_operator,
	imm_minus_operator,
	imm_mul_operator,
	imm_division_operator,
	decrement_operator,
	increment_operator,

	gt_operator,
	lt_operator,
	le_operator,
	lt_operator,

	identifier,

	opening_bracket,
	closing_bracket,

	opening_s_bracket,
	closing_s_bracket,

	opening_c_bracket,
	closing_c_bracket,

	string_type,
	char_type,
	int_type,
	float_type,

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
