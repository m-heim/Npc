#ifndef SCANNER_H
#define SCANNER_H
#include "token.h"
#include "symbol_table.h"
typedef struct {
	token_array *token_array;
	symbol_table *table;
} scanner_result;

void lexing_error(size_t position, size_t line, char *code, size_t length);

scanner_result lex(char *code, int debug, int export_symbol);

#endif
