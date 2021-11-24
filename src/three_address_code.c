#include "three_address_code.h"

three_address_code *three_address_code_make() {
    three_address_code *code;
    code->size = THREE_ADDRESS_CODE_INIT_SIZE;
    code->used = 0;
    code->arr = malloc(code->size * sizeof(three_address_code_entry));
}

void three_address_code_add(three_address_code *code, long label, three_address_code_op op, long x, long y, long z) {
    if(code->size == code->used) {
        code->arr = realloc(code->arr, code->size * sizeof(three_address_code_entry) * 2);
        code->size = code->size * 2;
    }
    (code->arr[code->used]).label = label;
    (code->arr[code->used]).operation = op;
    (code->arr[code->used]).x = x;
    (code->arr[code->used]).y = y;
    (code->arr[code->used]).z = z;
    code->used += 1;
}