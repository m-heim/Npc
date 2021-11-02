#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>

symbol_table * make_symbol_table() {
	// allocate memory for a table
	symbol_table *table = malloc(sizeof(symbol_table));
	// allocate memory for the id array ....
	table->id = malloc(SYMBOL_TABLE_INIT_SIZE * sizeof(long));
	table->position = malloc(SYMBOL_TABLE_INIT_SIZE * sizeof(long));
	table->line = malloc(SYMBOL_TABLE_INIT_SIZE * sizeof(long));
	table->value = malloc(SYMBOL_TABLE_INIT_SIZE * sizeof(void *));
	// Size is 10
	table->size = SYMBOL_TABLE_INIT_SIZE;
	// table is empty
	table->used = 0;
	return table;
}

// add an entry to the symbol table
void add_symbol_table_entry(symbol_table *table, long id, long position, long line, char *value) {
	// store the length
	long used = table->used;
	// if our array is full
	if (table->size == table->used) {
		// double the size of it
		table->id = realloc(table->id, table->size * 2 * sizeof(long));
		table->position = realloc(table->position, table->size * 2 * sizeof(long));
		table->line = realloc(table->position, table->size * 2 * sizeof(long));
		table->value = realloc(table->position, table->size * 2 * sizeof(long));
		table->size *= 2;
	}
	// assign each value to the next position in the arrays
	table->id[used] = id;
	table->position[used] = position;
	table->line[used] = line;
	// make storage for the value
	table->value[used] = malloc((strlen(value) + 1) * sizeof(char));
	// now copy value into that storage
	strcpy(table->value[used], value);
	// now we increment used;
	table->used += 1;

	return;
}

long get_symbol_position(symbol_table *table, long id) {
	return table->position[id];
}

long get_symbol_line(symbol_table *table, long id) {
	return table->line[id];
}

char *get_symbol_value(symbol_table *table, long id) {
	return table->value[id];
}
