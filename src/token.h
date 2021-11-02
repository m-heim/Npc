#ifndef TOKEN_H
#define TOKEN_H
#define TOKEN_ARRAY_INIT_SIZE
#include <stdlib.h>
typedef enum{
	assignment,

	plus_operator,
	minus_operator,
	multiplication_operator,
	division_operator,

	identifier,

	opening_bracket,
	closing_bracket,

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
	token *arr;
	size_t used;
	size_t size;
} token_array;

token_array *make_token_array();

token *make_token(token_type type, long value);

#endif
