#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#define SYMBOL_TABLE_INIT_SIZE 10
#include <stdlib.h>

typedef struct {
	long *id;
	long *position;
	long *line;
	char **value;
	size_t size;
	size_t used;
} symbol_table;

symbol_table *symbol_table_make();

void symbol_table_add(symbol_table *table, long id, long position, long line, char *value, size_t val_len);

long symbol_table_get_position(symbol_table *table, long id);

long symbol_table_get_line(symbol_table *table, long id);

char *symbol_table_get_value(symbol_table *table, long id);

#endif
