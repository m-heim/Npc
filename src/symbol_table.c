#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

symbol_table *symbol_table_make() {
	// allocate memory for a table
	symbol_table *table = malloc(sizeof(symbol_table));
	// allocate memory for the id array ....
	table->position =
		malloc(SYMBOL_TABLE_INIT_SIZE * sizeof(*(table->position)));
	table->line = malloc(SYMBOL_TABLE_INIT_SIZE * sizeof(size_t));
	table->value = malloc(SYMBOL_TABLE_INIT_SIZE * sizeof(void *));
	// Size is 10
	table->size = SYMBOL_TABLE_INIT_SIZE;
	// table is empty
	table->used = 0;
	return table;
}

// add an entry to the symbol table
void symbol_table_add(symbol_table *table, size_t position, size_t line,
					  char *value, size_t val_len) {
	// store the length
	size_t used = table->used;
	// if our array is full
	if (table->size == table->used) {
		// double the size of it
		table->position =
			realloc(table->position, table->size * 2 * sizeof(size_t));
		table->line = realloc(table->line, table->size * 2 * sizeof(size_t));
		table->value = realloc(table->value, table->size * 2 * sizeof(void *));
		table->size *= 2;
	}
	// assign each value to the next position in the arrays
	table->position[used] = position;
	table->line[used] = line;
	// make storage for the value
	char *copy_of_string = malloc((val_len + 1) * sizeof(char));
	// now copy value into that storage
	strncpy(copy_of_string, value, val_len);
	copy_of_string[val_len] = '\0';
	// now we increment used;
	table->value[table->used] = copy_of_string;
	table->used += 1;

	return;
}

long symbol_table_get_position(symbol_table *table, size_t id) {
	return table->position[id];
}

long symbol_table_get_line(symbol_table *table, size_t id) {
	return table->line[id];
}

char *symbol_table_get_value(symbol_table *table, size_t id) {
	return table->value[id];
}
void print_symbol_table(symbol_table *table) {
	for (size_t i = 0; i < table->used; i++) {
		printf("%ld\t %ld\t%s\n", symbol_table_get_position(table, i),
			   symbol_table_get_line(table, i),
			   symbol_table_get_value(table, i));
	}
}