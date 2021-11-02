#include "token.h"
#include "scanner.h"
#include "symbol_table.h"

token *lex(char *code) {
	symbol_table *table = symbol_table_make();
	token_array *arr = token_array_make();
	scanner_result result;
	result.table = table;
	result.tkn_array = arr;

}
