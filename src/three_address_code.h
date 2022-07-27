#ifndef THREE_ADDRESS_CODE_H
#define THREE_ADDRESS_CODE_H
#define THREE_ADDRESS_CODE_INIT_SIZE 10
#include <stdlib.h>

typedef enum three_address_code_op {
  // Jumps
  unconditional_jump,
  conditional_jump,
  conditional_jump_inversed,

  // copying
  copy_op,
  mem_copy_op,
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
  ne_op,

  funheader
} three_address_code_op;

typedef enum {
  address_int_literal,
  address_float_literal,
  address_char_literal,
  address_string_literal,
  address_variable,
  address_function,
  address_temporary,
  address_undefined,
  address_memory,
  address_size
} address_type;

typedef struct three_address_code_entry_address {
  address_type type;
  long value;
} three_address_code_entry_address;

typedef struct three_address_code_entry {
  long label;
  three_address_code_op operation;
  three_address_code_entry_address result;
  three_address_code_entry_address x;
  three_address_code_entry_address y;
} three_address_code_entry;

typedef struct three_address_code {
  size_t used;
  size_t size;
  three_address_code_entry *arr;
} three_address_code;

three_address_code *three_address_code_make();

void three_address_code_add(three_address_code *code, long label,
                            three_address_code_op op, address_type x_type,
                            long x, address_type y_type, long y,
                            address_type res_type, long res);

#endif