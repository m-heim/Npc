#include "ir_gen.h"
#include <string.h>
#include <stdio.h>
v_table *v_table_make() {
    v_table *table = malloc(sizeof(v_table));
    table->name = malloc(sizeof(char *) * V_TABLE_INIT_SIZE);
    table->used = 0;
    table->size = V_TABLE_INIT_SIZE;
    return table;
}

size_t v_table_add(v_table *table, const char *str) {
    if (table->size == table->used) {
        table->name = realloc(table->name, table->size * 2 * sizeof(char *));
        table->size *= 2;
    }
    table->name[table->used] = malloc((1 + strlen(str)));
    strcpy(table->name[table->used], str);
    return table->used ++;
}

const char * v_table_get(v_table *table, size_t id) {
    if(id >= table->used) {
        printf("IR_GEN: undefined error in ir generation. Programm will end.");
        _Exit(1);
    }
    return table->name[id];
}