#include "node.h"

// make a new node with the given type and the value which is an entry in the symbol table
node *node_make(node_type type, node_type_class type_class, long value) {
	node *n = malloc(sizeof(node));
	n->type = type;
	n->type_class = type_class;
	n->value = value;
	return n;
}

// make a new node array
node_array *node_array_make() {
	node_array *arr = malloc(sizeof(node_array));
	arr->node_array = malloc(sizeof(node) * NODE_ARRAY_INIT_SIZE);
	arr->used = 0;
	arr->size = NODE_ARRAY_INIT_SIZE;
	return arr;
}

node_type_class node_array_get_node_type_class(node_array *arr, long position) {
	return arr->node_array[position].type_class;
}

// add a new entry to the node array
void node_array_add(node_array *arr, node_type type, node_type_class type_class, long value) {
	if (arr->used == arr->size) {
		arr->node_array = realloc(arr->node_array, arr->size * 2 * sizeof(node));
		arr->size = arr->size * 2;
	}
	arr->node_array[arr->used].type = type;
	arr->node_array[arr->used].type_class = type_class;
	arr->node_array[arr->used].value = value;
	arr->used += 1;
}

// get the node type of a node
node_type node_array_get_node_type(node_array *arr, long position) {
	return (arr->node_array[position]).type;
}

// get a pointer to the node of an array
node *node_array_get_node(node_array *arr, long position) {
	return &(arr->node_array[position]);
}

long *node_array_get_val(node_array *arr, long position) {
	return &(arr->node_array[position].value);
}

char *node_type_get_canonial(node_type type) {
	if (type == identifier_token) {
		return "identifier_token";
	} else if (type == assignment_token) {
		return "assignment_token";
	} else if (type == imm_plus_operator_token) {
		return "imm_plus_operator_token";
	} else if (type == imm_minus_operator_token) {
		return "imm_minus_operator_token";
	} else if (type == imm_mul_operator_token) {
		return "imm_mul_operator_token";
	} else if (type == imm_division_operator_token) {
		return "imm_division_operator_token";
	} else if (type == selector_token) {
		return "selector_token";
	} else if (type == semicolon_token) {
		return "semicolon_token";
	} else if (type == colon_token) {
		return "colon_token";
	} else if (type == comma_token) {
		return "comma_token";
	} else if (type == program_directive_token) {
		return "program_directive_token";
	} else if (type == module_directive_token) {
		return "module_directive_token";
	} else if (type ==include_directive_token) {
		return "include_directive_token";
	} else if (type == macro_directive_token) {
		return "macro_directive_token";
	} else if (type == plus_operator_token) {
		return "plus_operator_token";
	} else if (type == minus_operator_token) {
		return "minus_operator_token";
	} else if (type == multiplication_operator_token) {
		return "multiplication_operator_token";
	} else if (type == division_operator_token) {
		return "division_operator_token";
	} else if (type == mod_operator_token) {
		return "mod_operator_token";
	} else if (type == pot_operator_token) {
		return "pot_operator_token";
	} else if (type == gt_operator_token) {
		return "gt_operator_token";
	} else if (type == lt_operator_token) {
		return "lt_operator_token";
	} else if (type == le_operator_token) {
		return "le_operator_token";
	} else if (type == ge_operator_token) {
		return "ge_operator_token";
	} else if (type == floor_div_operator_token) {
		return "floor_div_operator_token";
	} else if (type == decrement_operator_token) {
		return "decrement_operator_token";
	} else if (type == not_token) {
		return "not-token";
	} else if (type == increment_operator_token) {
		return "increment_operator_token";
	} else if (type == opening_bracket_token) {
		return "opening_bracket_token";
	} else if (type == closing_bracket_token) {
		return "closing_bracket_token";
	} else if (type == opening_c_bracket_token) {
		return "open_c_bracket";
	} else if (type == closing_c_bracket_token) {
		return "c_c_bracket";
	} else if (type == opening_s_bracket_token) {
		return "opening_s_bracket_token";
	} else if (type == closing_s_bracket_token) {
		return "opening_s_bracket_token";
	} else if (type == string_literal) {
		return "string_literal";
	} else if (type == char_literal) {
		return "char_literal";
	} else if (type == int_literal) {
		return "int_literal";
	} else if (type == float_literal) {
		return "float_literal";
	} else if (type == string_type_token) {
		return "string_type_token";
	} else if (type == char_type_token) {
		return "char_type_token";
	} else if (type == float_type_token) {
		return "float_type_token";
	} else if (type == int_type_token) {
		return "int_type_token";
	} else if (type == program_n) {
		return "program_n";
	} else if (type == module_n) {
		return "module_n";
	} else if (type == secondarydirective_n) {
		return "secondarydirective_n";
	} else if (type == secondarydirective_list_n) {
		return "secondarydirective_list_n";
	} else if (type == include_directive_n) {
		return "include_directive_n";
	} else if (type == include_directive_subselect_n) {
		return "include_directive_subselect_n";
	} else if (type == functions_n) {
		return "functions_n"; 
	} else if (type == program_directive_n) {
		return "program_directive_n";
	} else if (type == module_directive_n) {
		return "module_directive_n";
	} else if (type == macro_directive_n) {
		return "macro_directive_n";
	} else if (type == function_n) {
		return "function_n";
	} else if (type == unop_n) {
		return "unop_n";
	} else if (type == binop_n) {
		return "binop_n";
	} else if (type == parameter_n) {
		return "parameter_n";
	} else if (type == parameter_list_n) {
		return "parameter_list_n";
	} else if (type == type_n) {
		return "type_n";
	} else {
		return "Tes";
	}
}

char *node_type_get_class(node_type_class type ) {
	if (type == unop_c) {
		return "unop_c";
	} else if (type == binop_c) {
		return "binop_c";
	} else if (type == assign_c) {
		return "assign_";
	} else if (type == sec_directive_c) {
		return "sec_directive_c";
	} else if (type == prim_directive_c) {
		return "prim_directive_c";
	} else if (type == literal_c) {
		return "literal_c";
	} else if (type == type_c) {
		return "type_c";
	} else if (type == nont_c) {
		return "nont_c";
	} else if (type == keyword_c) {
		return "keyword_c";
	} else if (type == nac_c) {
		return "nac_c";
	} else if (type == bracket_c) {
		return "bracket_c";
	} else if (type == punctuation_c) {
		return "punctuation_c";
	} else if (type == directive_c) {
		return "directive_c";
	} else {
		return "hi";
	}
}