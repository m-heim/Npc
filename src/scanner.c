#include "node.h"
#include "scanner.h"
#include "symbol_table.h"
#include <stdlib.h>
#include "char_utils.h"
#include <stdio.h>
#include <string.h>

int debug = 0;

void lexing_error(size_t position, size_t line, char *code) {
	printf("Error on char %lu in line %lu\n", position, line);
	printf("%.20s\n", code);
	printf("^\n");
	exit(1);
}

scanner_result lex(char *code) {
	symbol_table *table = symbol_table_make();
	node_array *arr = node_array_make();

	scanner_result result;
	result.table = table;
	result.node_array = arr;

	size_t position = 0;
	size_t start_position = 0;
	size_t len = 0;

	char *cur = code;
	char *start = code;

	int state = 0;
	long line = 0;
	size_t node_index = 0;


	while (*(code + position) != '\0') {
		cur = code + position;
		if (debug == 0) {
			printf("c %c, s %d\n", *cur, state);
		}
		if (state == 0) {
			if (is_latin(cur) || is_underscore(cur)) {
				state = 1;
			} else if (*cur == ' ') {
				state = 200;
			} else if (*cur == '\n') {
				state = 201;
			} else if (*cur == '\t') {
				state = 202;
			} else if (*cur == '"') {
				state = 41;
			} else if (*cur == '\'') {
				state = 38;
			} else if (*cur == '+') {
				state = 4;
			} else if (*cur == '-') {
				state = 3;
			} else if (*cur == '>') {
				state = 24;
			} else if (*cur == '<') {
				state = 27;
			} else if (*cur == '*') {
				state = 31;
			} else if (*cur == '/') {
				state = 30;
			} else if (is_number(cur)) {
				state = 5;
			} else if (*cur == '(') {
				state = 121;
			} else if (*cur == ')') {
				state = 122;
			} else if (*cur == '{') {
				state = 123;
			} else if (*cur == '}') {
				state = 124;
			} else if (*cur == '[') {
				state = 126;
			} else if (*cur == ']') {
				state = 125;
			} else if (*cur == '=') {
				state = 127;
			} else if (*cur == '.') {
				state = 128;
			} else if (*cur == '%') {
				state = 129;
			} else if (*cur == ';') {
				state = 130;
			} else if (*cur == ':') {
				state = 131;
			} else if (*cur == '#') {
				state = 43;
			} else if (*cur == ','){
				state = 133;
			} else {
				lexing_error(start_position, line, cur);
			}
		// id
		} else if (state == 1) {
			if (is_latin(cur) || is_underscore(cur) || is_number(cur)) {
				state = 1;
			} else {
				state = 100;
			} // are {} valid?
		// plus
		} else if (state == 4) {
			if (*cur == '=') {
				state = 106;
			} else if (*cur == '+') {
				state = 107;
			} else if (is_number(cur)) {
				state = 5;
			} else {
				state = 108;
			}
		} else if (state == 3) {
			if (*cur == '-') {
				state = 104;
			} else if (*cur == '=') {
				state = 102;
			} else if (is_number(cur)) {
				state = 5;
			} else {
				state = 103;
			}
		} else if(state == 41) {
			if (*cur == '"') {
				state = 119;
			} else if (*cur == '\\') {
				state = 42;
			} else {
				state = 41;
			}
		} else if (state == 42) {
			state = 41;
		} else if (state == 43) {
			if (is_latin(cur)) {
				state = 43;
			} else {
				state = 132;
			}
		} else if (state == 38) {
			state = 39;
		} else if (state == 39) {
			if (*cur == '\'') {
				state = 120;
			} else {
				lexing_error(start_position, line, cur);
			}
		} else if (state == 5) {
			if (*cur == '.') {
				state = 6;
			} else if (is_number(cur)) {
				state = 5;
			} else {
				state = 105;
			}
		} else if (state == 6) {
			if (is_number(cur)) {
				state = 6;
			} else {
				state = 101;
			}
		} else if (state == 24) {
			if (*cur == '=') {
				state = 110;
			} else {
				state = 109;
			}
		} else if (state == 27) {
			if (*cur == '=') {
				state = 112;
			} else {
				state = 111;
			}
		} else if (state == 31) {
			if (*cur == '*') {
				state = 115;
			} else if (*cur == '=') {
				state = 114;
			} else {
				state = 113;
			}
		} else if (state == 30) {
			if (*cur == '/') {
				state = 118;
			} else if (*cur == '=') {
				state = 117;
			} else {
				state = 116;
			}
		}
		if (state > 99 && state <= 199) {
			node_type ntype;
			node_type_class type_class;
			if (state == 100) {
				ntype = identifier_token;
				type_class = nac_c;
				position--;
				len = position - start_position + 1;
				if (strncmp(start, "int", len) == 0) {
					ntype = int_type_token;
					type_class = type_c;
				} else if (strncmp(start, "string", len) == 0) {
					ntype = string_type_token;
					type_class = type_c;
				} else if (strncmp(start, "char", len) == 0) {
                    ntype = char_type_token;
					type_class = type_c;
				} else if (strncmp(start, "float", len) == 0) {
                    ntype = float_type_token;
					type_class = type_c;
                }
			} else if (state == 102) {
				ntype = imm_plus_operator_token;
				type_class = assign_c;
			} else if (state == 103) {
				ntype = plus_operator_token;
				type_class = binop_c;
			} else if (state == 104) {
				ntype = increment_operator_token;
				type_class = unop_c;
			} else if (state == 105) {
				ntype = int_literal;
				position--;
				type_class = literal_c;
			} else if (state == 101) {
				position--;
				ntype = float_literal;
				type_class = literal_c;
			} else if (state == 106) {
				ntype = imm_minus_operator_token;
				type_class = assign_c;
			} else if (state == 107) {
				ntype = decrement_operator_token;
				type_class = unop_c;
			} else if (state == 108) {
				ntype = minus_operator_token;
				type_class = binop_c;
			} else if (state == 109) {
				ntype = gt_operator_token;
				type_class = binop_c;
				position--;
			} else if (state == 110) {
				ntype = ge_operator_token;
				type_class = binop_c;
			} else if (state == 111) {
				ntype = lt_operator_token;
				type_class = binop_c;
				position--;
			} else if (state == 112) {
				ntype = le_operator_token;
				type_class = binop_c;
			} else if (state == 113) {
				ntype = multiplication_operator_token;
				type_class = binop_c;
			} else if (state == 114) {
				ntype = imm_mul_operator_token;
				type_class = assign_c;
			} else if (state == 115) {
				ntype = pot_operator_token;
				type_class = binop_c;
			} else if (state == 116) {
				ntype = division_operator_token;
				type_class = binop_c;
			} else if (state == 117) {
				ntype = imm_division_operator_token;
				type_class = assign_c;
			} else if (state == 118) {
				ntype = floor_div_operator_token;
				type_class = binop_c;
			} else if (state == 119) {
				ntype = string_literal;
				type_class = literal_c;
			} else if (state == 120) {
				ntype = char_literal;
				type_class = literal_c;
			} else if (state == 121) {
				ntype = opening_bracket_token;
				type_class = bracket_c;
			} else if (state == 122) {
				ntype = closing_bracket_token;
				type_class = bracket_c;
			} else if (state == 123) {
				ntype = opening_c_bracket_token;
				type_class = bracket_c;
			} else if (state == 124) {
				ntype = closing_c_bracket_token;
				type_class = bracket_c;
			} else if (state == 125) {
				ntype = closing_s_bracket_token;
				type_class = bracket_c;
			} else if (state == 126) {
				ntype = opening_s_bracket_token;
				type_class = bracket_c;
			} else if (state == 127) {
				ntype = assignment_token;
				type_class = assign_c;
			} else if (state == 128) {
				ntype = selector_token;
				type_class = punctuation_c;
			} else if (state == 129) {
				ntype = mod_operator_token;
				type_class = binop_c;
			} else if (state == 130) {
				ntype = semicolon_token;
				type_class = punctuation_c;
			} else if (state == 131) {
				ntype = colon_token;
				type_class = punctuation_c;
			} else if (state == 132) {
				position--;
				len = position - start_position + 1;
				printf("%ld\n", len);
				if (strncmp(start, "#PROGRAM", len) == 0) {
					ntype = program_directive_token;
					type_class = prim_directive_c;
				} else if (strncmp(start, "#MODULE", len) == 0) {
					ntype = module_directive_token;
					type_class = prim_directive_c;
				} else if (strncmp(start, "#using", len) == 0) {
                    ntype = include_directive_token;
					type_class = sec_directive_c;
				} else if (strncmp(start, "#macro", len) == 0) {
                    ntype = macro_directive_token;
					type_class = sec_directive_c;
                } else {
					lexing_error(start_position, line, cur);
				}
			} else if (state == 133) {
				ntype = comma_token;
				type_class = punctuation_c;
			} else {
				printf("Not implemented, state %d", state);
				lexing_error(start_position, line, cur);
			}
			// re set cur because we did position-- above;
			cur = code + position;
			// get length of the token
			len = cur - start;

			node_array_add(arr, ntype, type_class, node_index);
			if (debug == 0) {
				printf("Added %s\n", node_type_get_canonial(ntype));
			}
			symbol_table_add(table, node_index, start_position, line, start, len);
			node_index++;
			start = cur + 1;
			start_position = position + 1;
			state = 0;
		} else if (state > 199) {
			if (state == 200) {
				state = 0;
			} else if (state == 201) {
				line++;
				state = 0;
			} else if (state == 202) {
				state = 0;
			}
			start = cur + 1;
			start_position = position + 1;
		} else if (state > 299) {
			state = 0;
		}
		position++;
	}
	return result;


}
