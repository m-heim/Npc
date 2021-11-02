#include "token.h"

token *make_token(token_type type, long value) {
	token *tkn = malloc(sizeof(token));
	tkn->type = type;
	tkn->value = value;
	return tkn;
}

token_array *make_token_array() {
	token_array *arr = malloc(sizeof(token_array));
	arr->arr = malloc(sizeof(token) * TOKEN_ARRAY_INIT_SIZE);
	arr->used = 0;
	arr->size = TOKEN_ARRAY_INIT_SIZE;
	return arr;
}

void add_token(token_array *arr, token tkn) {
	if (arr->used == arr->size) {
		arr->arr = malloc(arr->size * 2 * sizeof(token));
		arr->size *= 2;
	}
	arr->arr[arr->used] = tkn;
	arr->used += 1;
}
