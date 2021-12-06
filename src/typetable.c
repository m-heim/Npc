#include "typetable.h"

size_t typetable_get_size(typetable *table, int id) {
    return table->size[id];
}