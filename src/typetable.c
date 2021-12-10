#include "typetable.h"
#include <string.h>

size_t typetable_get_size(typetable *table, int id) {
    return table->type_size[id];
}

typetable *typetable_make() {
    typetable *table = malloc(sizeof(typetable));
    table->size = TYPETABLE_INIT_SIZE;
    table->used = 0;
    table->type_size = malloc(sizeof(size_t) * TYPETABLE_INIT_SIZE);
    table->name = malloc(sizeof(char *) * TYPETABLE_INIT_SIZE);
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

size_t typetable_get_by_name(typetable *table, char *name) {
    for(int i = 0; i < table->used; i++) {
        if (strcmp(table->name[i], name) == 0) {
            return table->type_size[i];
        }
    }
    return 0;
}