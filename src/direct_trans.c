#include "parser.h"
#define CODE_INIT_SIZE 1000

// Generate machine code based on the output of the parser
char* generate(parser_result parser_out)
{
	char* code = malloc(CODE_INIT_SIZE * sizeof(char));

	ast* tree = parser_out.tree;
	symbol_table* table = parser_out.table;
	node* curr;
	while (1) {
	}
}

ir_gen_result* translate(char* code, ast* tree, symbol_table* table, long place)
{
	switch (tree->n.type) {
	case function_n:
		three_address_code_add(i_result->code, MAXIMUM_LABEL, funheader, UNDEFINED, UNDEFINED, UNDEFINED);
		if (tree->children[2]->n.type == parameter_list_n) {
			long offset = 0;
			for (int i = 0; i < tree->children[2]->used; i++) {
				three_address_code_add(i_result->code, MAXIMUM_LABEL, mem_copy_op, long x, long y, long z)
			}
		}

	case expression_n:
		if (tree->used == 3) {
			long place1 = new_var();
			long place2 = new_var();
			translate(i_result, tree, table, place1);
			translate(i_result, tree, table, place2);
			three_address_code_add(i_result->code, MAXIMUM_LABEL, get_op(tree->children[1]->n.type), place, place1, place2);
		} else if (tree->used == 1) {
			long place1 = new_var();
			translate(i_result, tree, table, place1);
		} else {
			ir_gen_err();
		}
		break;
	case simple_expression_n:
		if (tree->used == 3) {
			long place1 = new_var();
			long place2 = new_var();
			translate(i_result, tree, table, place1);
			translate(i_result, tree, table, place2);
			three_address_code_add(i_result->code, MAXIMUM_LABEL, get_op(tree->children[1]->n.type), place, place1, place2);
		} else if (tree->used == 1) {
			long place1 = new_var();
			translate(i_result, tree, table, place1);
		} else {
			ir_gen_err();
		}
		break;
	case term_n:
		if (tree->used == 3) {
			long place1 = new_var();
			long place2 = new_var();
			translate(i_result, tree, table, place1);
			translate(i_result, tree, table, place2);
			three_address_code_add(i_result->code, MAXIMUM_LABEL, get_op(tree->children[1]->n.type), place, place1, place2);
		} else if (tree->used == 1) {
			long place1 = new_var();
			translate(i_result, tree, table, place1);
		} else {
			ir_gen_err();
		}
		break;
	case factor_n:
		if (tree->used == 3) {
			long place1 = new_var();
			translate(i_result, tree, table, place1);
			three_address_code_add(i_result->code, MAXIMUM_LABEL, get_op(tree->children[1]->n.type), place, place1, );
		} else if (tree->used == 1) {
			long place1 = new_var();
			translate(i_result, tree, table, place1);
		} else {
			ir_gen_err();
		}
		break;
	default:
	}
}
}