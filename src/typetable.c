#include "typetable.h"
#include <stdlib.h>
#include <string.h>

size_t typetable_get_size(typetable *table, int id) {
    return table->type_size[id];
}

typetable *typetable_make() {
    typetable *table = malloc(sizeof(typetable));
    table->name = malloc(TYPETABLE_INIT_SIZE * sizeof(char *));
    table->type_size = malloc(TYPETABLE_INIT_SIZE * sizeof(size_t));
    table->size = TYPETABLE_INIT_SIZE;
    table->used = 0;
    return table;
}

void typetable_add(typetable *table, char *name, size_t size) {
    if (table->size == table->used) {
        table->name = realloc(table->name, table->size * 2 * sizeof(char *));
        table->type_size = realloc(table->type_size, table->size * 2 * sizeof(size_t));
        table->size = table->size * 2;
    }
    table->type_size[table->used] = size;
    long len = (strlen(name) + 1) * sizeof(char);
    char *copy = malloc(len);
    strcpy(copy, name);
    copy[len - 1] = '\0';
    table->name[table->used] = copy;
    table->used += 1;
    return;
}

// Returns 1 if a type exists
int typetable_exists(typetable *table, char *name) {
    for(int i = 0; i < table->used; i++) {
        if (strcmp(table->name[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}