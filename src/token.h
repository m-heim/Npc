#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
enum tokenType {
	equals_operator,
	plus_operator,
	minus_operator,
	identifier,
	opening_bracket,
	closing_bracket,
	string_type,
	char_type,
	return_keyword,
	for_keyword,
	while_keyword,
	if_keyword,
	else_keyword
};

typedef struct {
	enum tokenType type;
	char *content;
} token;

token *new_token(enum tokenType type, char *content);

#endif
