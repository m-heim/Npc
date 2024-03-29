#include "token.h"
#include <stdio.h>

// make a new token with the given type and the value which is an entry in the
// symbol table
token *token_make(token_type type, token_type_class type_class, size_t position) {
	token *n = malloc(sizeof(token));
	n->type = type;
	n->type_class = type_class;
	n->position = position;
	return n;
}

// make a new token array
token_array *token_array_make() {
	token_array *arr = malloc(sizeof(token_array));
	arr->token_array = malloc(sizeof(token) * token_array_INIT_SIZE);
	arr->used = 0;
	arr->size = token_array_INIT_SIZE;
	return arr;
}

token_type_class token_array_get_token_type_class(token_array *arr, size_t index) {
	return arr->token_array[index].type_class;
}

// add a new entry to the token array
void token_array_add(token_array *arr, token_type type, token_type_class type_class,
					size_t position) {
	if (arr->used == arr->size) {
		arr->token_array =
			realloc(arr->token_array, arr->size * 2 * sizeof(token));
		arr->size = arr->size * 2;
	}
	arr->token_array[arr->used].type = type;
	arr->token_array[arr->used].type_class = type_class;
	arr->token_array[arr->used].position = position;
	arr->used += 1;
}

// get the token type of a token
token_type token_array_get_token_type(token_array *arr, size_t index) {
	return (arr->token_array[index]).type;
}

// get a pointer to the token of an array
token *token_array_get_token(token_array *arr, size_t index) {
	return &(arr->token_array[index]);
}


void print_tokens(token_array *arr) {
	for (int i = 0; i < arr->used; i++) {
		printf("%i %s\n", i,
			   token_type_get_canonial(token_array_get_token_type(arr, i)));
	}
}

char *token_type_get_canonial(token_type type) {
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
	} else if (type == include_directive_token) {
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
	} else if (type == string_literal_token) {
		return "string_literal_token";
	} else if (type == char_literal_token) {
		return "char_literal_token";
	} else if (type == int_literal_token) {
		return "int_literal_token";
	} else if (type == float_literal_token) {
		return "float_literal_token";
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
	} else if (type == block_n) {
		return "block_n";
	} else if (type == declaration_n) {
		return "declaration_n";
	} else if (type == simple_expression_n) {
		return "simple_expression_n";
	} else if (type == expression_n) {
		return "expression_n";
	} else if (type == factor_n) {
		return "factor_n";
	} else if (type == term_n) {
		return "term_n";
	} else if (type == if_statement_n) {
		return "if_statement_n";
	} else if (type == statement_n) {
		return "statement_n";
	} else if (type == return_statement_n) {
		return "return_statement_n";
	} else if (type == for_statement_n) {
		return "for_statement_n";
	} else if (type == function_call_n) {
		return "fun_call_n";
	} else if (type == argument_list_n) {
		return "argument_list_n";
	} else if (type == argument_n) {
		return "argument_n";
	} else if (type == return_keyword_token) {
		return "return_keyword_token";
	} else if (type == for_keyword_token) {
		return "for_keyword_token";
	} else if (type == if_keyword_token) {
		return "IF_keyword_token";
	} else if (type == long_type_token) {
		return "long_type_token";
	} else if (type == end_directive_token) {
		return "end_directive_token";
	} else {
		return "Tes";
	}
}

char *token_type_get_class(token_type_class type) {
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
		return "undefined_class";
	}
}