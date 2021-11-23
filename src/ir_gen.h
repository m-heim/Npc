#ifndef IR_GEN_H
#define IR_GEN_H
#include "parser.h"
#define V_TABLE_INIT_SIZE 10

typedef struct ir_gen_result {

} ir_gen_result;

typedef struct three_address_code {

} three_address_code;

typedef enum three_address_code_op {
    // Jumps
    unconditional_jump,
    conditional_jump,
    conditional_jump_inversed,

    // copying
    copy,
    indexed_copy,

    // unary
    minus,
    log_negation,
    conversion,
    inc,
    dec,
    // binary_instructions

    add,
    subtract,
    multiply,
    divide,
    modulo,
    pot,

    // relop
    gt,
    le,
    lt,
    ge,
    eq,
    ne
} three_address_code_op;

typedef struct three_address_code_entry {
    long label;
    three_address_code_op operation;
    long 
    
} three_address_code_entry;

typedef struct v_table {
    char **name;
    size_t size;
    size_t used;
} v_table;

v_table *v_table_make();
size_t v_table_add(v_table *table, const char *str);
const char * v_table_get(v_table *table, size_t id);

three_address_code three_address_code_generator(parser_result result);
#endif