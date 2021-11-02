#ifndef SCANNER_H
#define SCANNER_H
#include "symbol_table.h"
#include "token.h"
typedef struct {
	token_array *tkn_array;
	symbol_table *table;
} scanner_result;

#endif
