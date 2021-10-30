#include "token.h"

token *new_token(enum tokenType type, char *content) {
	token *tkn = malloc(sizeof(token));
	tkn->type = type;
	tkn->content = content;
	return tkn;
}
