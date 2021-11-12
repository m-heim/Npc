#ifndef SCANNER_H
#define SCANNER_H
#include "symbol_table.h"
#include "node.h"
typedef struct {
	node_array *node_array;
	symbol_table *table;
} scanner_result;

void lexing_error(size_t position, size_t line, char *code);

scanner_result lex(char *code);

#endif
