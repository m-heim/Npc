#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#define SYMBOL_TABLE_INIT_SIZE 10
#include <stdlib.h>

typedef struct {
	size_t *position;
	size_t *line;
	char **value;
	size_t size;
	size_t used;
} symbol_table;

symbol_table *symbol_table_make();

void symbol_table_add(symbol_table *table, size_t position, size_t line,
					  char *value, size_t val_len);

long symbol_table_get_position(symbol_table *table, size_t id);

long symbol_table_get_line(symbol_table *table, size_t id);

char *symbol_table_get_value(symbol_table *table, size_t id);
void print_symbol_table(symbol_table *table);
#endif
