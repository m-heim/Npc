#ifndef TYPETABLE_H
#define TYPETABLE_H
#define TYPETABLE_INIT_SIZE 10

#include <stdlib.h>

// The type typetable is a list that holds the name of the type and the size of the type in Byte!
typedef struct typetable {
    char **name;
    size_t *type_size;
    size_t used;
    size_t size;
} typetable;

// Get the size of the typetable
size_t typetable_get_size(typetable *table, int id);
// make a new typetable
typetable *typetable_make();
// add a new type to the typetable
void typetable_add(typetable *table, char *name, size_t size);
// checks wether a given type exists
int typetable_exists(typetable *table, char *name);

#endif