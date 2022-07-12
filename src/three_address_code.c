#include "three_address_code.h"

three_address_code* three_address_code_make()
{
	three_address_code* code;
	code->size = THREE_ADDRESS_CODE_INIT_SIZE;
	code->used = 0;
	code->arr = malloc(code->size * sizeof(three_address_code_entry));
	return code;
}

void three_address_code_add(three_address_code* code, long label, three_address_code_op op, address_type x_type, long x, address_type y_type, long y, address_type res_type, long res)
{
	if (code->size == code->used) {
		code->arr = realloc(code->arr, code->size * sizeof(three_address_code_entry) * 2);
		code->size = code->size * 2;
	}
	(code->arr[code->used]).label = label;
	(code->arr[code->used]).operation = op;
	(code->arr[code->used]).x.value = x;
	(code->arr[code->used]).x.type = x_type;
	(code->arr[code->used]).result.value = res;
	(code->arr[code->used]).result.type = res_type;
	(code->arr[code->used]).y.value = y;
	(code->arr[code->used]).y.type = y_type;
	code->used += 1;
}