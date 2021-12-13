#ifndef TYPETABLE_H
#define TYPETABLE_H
#define TYPETABLE_INIT_SIZE 10

#include <stdlib.h>

typedef struct typetable {
    char **name;
    size_t *type_size;
    size_t used;
    size_t size;
} typetable;

size_t typetable_get_size(typetable *table, int id);
typetable *typetable_make();
void typetable_add(typetable *table, char *name, size_t size);
int typetable_exists(typetable *table, char *name);

#endif