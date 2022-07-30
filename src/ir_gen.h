#ifndef IR_GEN_H
#define IR_GEN_H
#define V_TABLE_INIT_SIZE 10
#define MAXIMUM_LABEL 9223372036854775807
#define UNDEFINED -1
#include "parser.h"
#include "three_address_code.h"
typedef struct v_table {
	char **name;
	size_t size;
	size_t used;
} v_table;

typedef struct ir_gen {
	parser_result parser_result;
	v_table v_table;
	three_address_code code;
} ir_gen;

/**
* @brief Holds the output of the intermediate repr. generation, consists of the corresponding three address code and the
*/
typedef struct ir_gen_result {
	three_address_code *code;
	v_table *table;
} ir_gen_result;

v_table *v_table_make();
size_t v_table_add(v_table *table, const char *str);
const char *v_table_get(v_table *table, size_t id);
ir_gen_result generate(parser_result parser_out);

three_address_code_op get_op(token_type type);
long new_var();
#endif