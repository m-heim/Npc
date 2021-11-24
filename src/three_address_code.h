#ifndef THREE_ADDRESS_CODE_H
#define THREE_ADDRESS_CODE_H
#define THREE_ADDRESS_CODE_INIT_SIZE 10
#include <stdlib.h>

typedef struct three_address_code {
    size_t used;
    size_t size;
    three_address_code_entry *arr;
} three_address_code;

typedef enum three_address_code_op {
    // Jumps
    unconditional_jump,
    conditional_jump,
    conditional_jump_inversed,

    // copying
    copy_op,
    indexed_copy_op,

    // unary
    minus_op,
    log_negation_op,
    conversion_op,
    inc_op,
    dec_op,
    // binary_instructions

    add_op,
    subtract_op,
    multiply_op,
    divide_op,
    modulo_op,
    pot_op,

    // relop
    gt_op,
    le_op,
    lt_op,
    ge_op,
    eq_op,
    ne_op
} three_address_code_op;

typedef struct three_address_code_entry {
    long label;
    three_address_code_op operation;
    long x;
    long y;
    long z;
} three_address_code_entry;

three_address_code *three_address_code_make();

void three_address_code_add(three_address_code *code, long label, three_address_code_op op, long x, long y, long z);

#endif