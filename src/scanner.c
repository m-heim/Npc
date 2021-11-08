#include "node.h"
#include "scanner.h"
#include "symbol_table.h"
#include <stdlib.h>
#include "char_utils.h"
#include <stdio.h>
#include <string.h>

void lexing_error(size_t position, size_t line) {
	printf("Error on char %lu in line %lu\n", position, line);
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
	size_t line = 0;
	size_t node_index = 0;


	while (*(code + position) != '\0') {
		cur = code + position;
		printf("Current char is %c, state is %d\n", *cur, state);
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
				lexing_error(position, line);
			}
		// id
		} else if (state == 1) {
			if (is_latin(cur) || is_underscore(cur) || is_number(cur)) {
				state = 1;
			} else {
				state = 100;
			} // are {} valid?
		// plus
		} else if (state == 3) {
			if (*cur == '=') {
				state = 106;
			} else if (*cur == '+') {
				state = 107;
			} else if (is_number(cur)) {
				state = 5;
			} else {
				state = 108;
			}
		} else if (state == 4) {
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
				lexing_error(position, line);
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
			node_type type;
			if (state == 100) {
				type = identifier_token;
				position--;
				if (strncmp(start, "int", len)) {
					type = int_type_type_token;
				} else if (strncmp(start, "string", len)) {
					type = string_type_type_token;
				} else if (strncmp(start, "char", len)) {
                    type = char_type_type_token;
				} else if (strncmp(start, "float", len)) {
                    type = float_type_type_token;
                }
			} else if (state == 102) {
				type = imm_minus_operator_token;
			} else if (state == 103) {
				type = minus_operator_token;
			} else if (state == 104) {
				type = decrement_operator_token;
			} else if (state == 105) {
				type = int_type_token;
				position--;
			} else if (state == 101) {
				position--;
				type = float_type_token;
			} else if (state == 106) {
				type = imm_plus_operator_token;
			} else if (state == 107) {
				type = increment_operator_token;
			} else if (state == 108) {
				type = plus_operator_token;
			} else if (state == 109) {
				type = gt_operator_token;
				position--;
			} else if (state == 110) {
				type = ge_operator_token;
			} else if (state == 111) {
				type = lt_operator_token;
				position--;
			} else if (state == 112) {
				type = le_operator_token;
			} else if (state == 113) {
				type = multiplication_operator_token;
			} else if (state == 114) {
				type = imm_mul_operator_token;
			} else if (state == 115) {
				type = pot_operator_token;
			} else if (state == 116) {
				type = division_operator_token;
			} else if (state == 117) {
				type = imm_division_operator_token;
			} else if (state == 118) {
				type = floor_div_operator_token;
			} else if (state == 119) {
				type = string_type_token;
			} else if (state == 120) {
				type = char_type_token;
			} else if (state == 121) {
				type = opening_bracket_token;
			} else if (state == 122) {
				type = closing_bracket_token;
			} else if (state == 123) {
				type = opening_c_bracket_token;
			} else if (state == 124) {
				type = closing_c_bracket_token;
			} else if (state == 125) {
				type = closing_s_bracket_token;
			} else if (state == 126) {
				type = opening_s_bracket_token;
			} else if (state == 127) {
				type = assignment_token;
			} else if (state == 128) {
				type = selector_token;
			} else if (state == 129) {
				type = mod_operator_token;
			} else if (state == 130) {
				type = semicolon_token;
			} else if (state == 131) {
				type = colon_token;
			} else if (state == 132) {
				type = directive_token;
				len = position - start_position + 1;
				position--;
				if (strncmp(start, "#PROGRAM", len)) {
					type = program_directive_token;
				} else if (strncmp(start, "#MODULE", len)) {
					type = module_directive_token;
				} else if (strncmp(start, "#using", len)) {
                    type = include_directive_token;
				} else if (strncmp(start, "#macro", len)) {
                    type = macro_directive_token;
                }
			} else if (state == 133) {
				type = comma_token;
			} else {
				printf("Not implemented, state %d", state);
			}
			printf("Found %d\n", state);
			cur = code + position;
			len = cur - start;

			node_array_add(arr, type, node_index);
			symbol_table_add(table, node_index, (long) start_position, line, start, len);

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
		} else if (state > 299) {
			state = 0;
		}
		position++;
	}
	return result;


}
