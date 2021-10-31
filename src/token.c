#include "token.h"

token *new_token(token_type type, long value) {
	token *tkn = malloc(sizeof(token));
	tkn->type = type;
	tkn->value = value;
	return tkn;
}
