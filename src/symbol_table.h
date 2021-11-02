#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#define SYMBOL_TABLE_INIT_SIZE = 10;
#inluce <stdlib.h>

typedef struct {
	long *id;
	long *position;
	long *line;
	char **value;
	size_t size;
	size_t used;
} symbol_table;

symbol_table *make_symbol_table();

void add_symbol_table_entry(symbol_table *table, long id, long position, long line, char *value);

#endif
