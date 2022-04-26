#ifndef SCANNER_H
#define SCANNER_H
#include "node.h"
#include "symbol_table.h"
typedef struct {
	node_array* node_array;
	symbol_table* table;
} scanner_result;

void lexing_error(size_t position, long line, char* code);

scanner_result lex(char* code);

#endif
