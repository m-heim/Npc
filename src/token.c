#include "token.h"

token *token_make(token_type type, long value) {
	token *tkn = malloc(sizeof(token));
	tkn->type = type;
	tkn->value = value;
	return tkn;
}

token_array *token_array_make() {
	token_array *arr = malloc(sizeof(token_array));
	arr->tkn_array = malloc(sizeof(token) * TOKEN_ARRAY_INIT_SIZE);
	arr->used = 0;
	arr->size = TOKEN_ARRAY_INIT_SIZE;
	return arr;
}

void token_array_add(token_array *arr, token_type type, long value) {
	if (arr->used == arr->size) {
		arr->tkn_array = realloc(arr->tkn_array, arr->size * 2 * sizeof(token));
		arr->size *= 2;
	}
	arr->tkn_array[arr->used].type = type;;
	arr->tkn_array[arr->used].value = value;
	arr->used += 1;
}

token_type token_array_get_token_type(token_array *arr, long position) {
	return (arr->tkn_array[position]).type;
}

token *token_array_get_token(token_array *arr, long position) {
	return arr->tkn_array[position];
}
