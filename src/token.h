#ifndef TOKEN_H
#define TOKEN_H

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

token *new_token(token_type type, long value);

#endif
