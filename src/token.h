#ifndef token_H
#define token_H
#define token_array_INIT_SIZE 10
#include <stdlib.h>

/**
 * @brief The types provided for lexing and parsing
 * @author Maximilian Heim (MaximilianHeim@protonmail.com)
 * @date 2022-07-28
 * @version 0.1
 */
typedef enum token_type {
	identifier_token,
	assignment_token,

	///@{
	/* operators += /= *= -= */
	imm_minus_operator_token,
	imm_plus_operator_token,
	imm_mul_operator_token,
	imm_division_operator_token,
	///@}

	selector_token,
	semicolon_token,
	colon_token,
	comma_token,

	// DIRECTIVES
	program_directive_token,
	end_directive_token,
	module_directive_token,
	include_directive_token,
	macro_directive_token,

	// BINARY OPERATORS
	plus_operator_token,
	minus_operator_token,
	multiplication_operator_token,
	division_operator_token,
	mod_operator_token,
	pot_operator_token,
	gt_operator_token,
	lt_operator_token,
	le_operator_token,
	ge_operator_token,
	floor_div_operator_token,

	// UNARY OPERATORS
	increment_operator_token,
	not_token,
	decrement_operator_token,

	// STRUCTURE //
	opening_bracket_token,
	closing_bracket_token,

	opening_s_bracket_token,
	closing_s_bracket_token,

	opening_c_bracket_token,
	closing_c_bracket_token,

	// Literals
	string_literal_token,
	char_literal_token,
	int_literal_token,
	float_literal_token,

	// types
	string_type_token,
	char_type_token,
	int_type_token,
	float_type_token,
	long_type_token,

	return_keyword_token,
	continue_keyword_token,
	break_keyword_token,
	for_keyword_token,
	while_keyword_token,
	if_keyword_token,
	else_keyword_token,
	elif_keyword_token,
	function_token,

	// Ntm
	if_statement_n,
	return_statement_n,
	continue_statement_n,
	break_statement_n,
	for_statement_n,
	expression_n,
	factor_n,
	term_n,
	program_n,
	declaration_n,
	functioncall_n,
	argument_n,
	argument_list_n,
	block_n,
	var_n,
	module_n,
	secondarydirective_n,
	secondarydirective_list_n,
	include_directive_n,
	include_directive_subselect_n,
	program_directive_n,
	module_directive_n,
	macro_directive_n,
	function_n,
	functions_n,
	unop_n,
	binop_n,
	parameter_n,
	parameter_list_n,
	type_n,
	statement_n,
	jump_statement_n,
	expression_statement_n,
	simple_expression_n,
	function_call_n

} token_type;

typedef enum token_type_class {
	unop_c,
	binop_c,
	assign_c,
	sec_directive_c,
	prim_directive_c,
	literal_c,
	type_c,
	nont_c,
	keyword_c,
	nac_c,
	bracket_c,
	punctuation_c,
	directive_c,
	relop_c

} token_type_class;

typedef struct token {
	token_type type;
	token_type_class type_class;
	size_t position;
} token;

typedef struct token_array {
	token *token_array;
	size_t used;
	size_t size;
} token_array;

token_array *token_array_make();
void token_array_add(token_array *arr, token_type type,
					 token_type_class type_class, size_t position);

token_type token_array_get_token_type(token_array *arr, size_t index);
token_type_class token_array_get_token_type_class(token_array *arr,
												  size_t index);

token *token_array_get_token(token_array *arr, size_t index);

void print_tokens(token_array *arr);

token *token_make(token_type type, token_type_class type_class,
				  size_t position);

char *token_type_get_canonial(token_type type);

char *token_type_get_class(token_type_class type);

#endif
