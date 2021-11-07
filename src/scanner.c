#include "token.h"
#include "scanner.h"
#include "symbol_table.h"
#include <stdlib.h>
#include "char_utils.h"

void lexing_error(size_t position, size_t line) {
	printf("Error on char %lu in line %lu\n", position, line);
	exit(1);
}

token *lex(char *code) {
	symbol_table *table = symbol_table_make();
	token_array *arr = token_array_make();
	scanner_result result;
	result.table = table;
	result.tkn_array = arr;
	//int transition[43][128] = {};
	size_t position = 0;
	char *cur;
	int state = 0;
	size_t line = 0;
	size_t token_len = 0;
	size_t token_index = 0;


	while (code + position != '\0') {
		cur = code + position;
		if (state == 0) {
			if (is_latin(cur) || is_underscore(cur)) {
				state = 1;
			} else if (*cur == ' ') {
				state = 200;
			} else if (*cur == '\n') {
				state = 201;
			} else if (*cur == '"') {
				state = 41;
			} else if (*cur == ''') {
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
				state = 121
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
			} else {
				lexing_error(position, line);
			}
		// id
		} else if (state == 1) {
			if (is_latin(cur) || is_underscore(cur || is_number(cur)) {
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
			} else if (*cur == '\') {
				state = 42;
			} else {
				state = 41;
			}
		} else if (state == 42) {
			state = 41;
		} else if (state == 38) {
			state = 39;
		} else if (state == 39) {
			if (*cur == ''') {
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
			token_type type;
			if (state == 100) {
				type = identifier;
				position--;
				token_len--;
			} else if (state == 102) {
				type = imm_minus_operator;
			} else if (state == 103) {
				type = minus_operator;
			} else if (state == 104) {
				type = decrement_operator;
			} else if (state == 105) {
				type = int_type;
				position--;
				token_len--;
			} else if (state == 101) {
				position--;
				type = float_type;
				token_len--;
			} else if (state == 106) {
				type = imm_plus_operator;
			} else if (state == 107) {
				type = increment_operator;
			} else if (state == 108) {
				type = plus_operator;
			} else if (state == 109) {
				type = gt_operator;
				position--;
				token_len--;
			} else if (state == 110) {
				type = ge_operator;
			} else if (state == 111) {
				type = lt_operator;
				position--;
				token_len--;
			} else if (state == 112) {
				type = le_operator;
			} else if (state == 113) {
				type = multiplication_operator;
			} else if (state == 114) {
				type = imm_mul_operator;
			} else if (state == 115) {
				type = pot_operator;
			} else if (state == 116) {
				type = division_operator;
			} else if (state == 117) {
				type = imm_division_operator;
			} else if (state == 118) {
				type = floor_division_operator;
			} else if (state == 119) {
				type = string_type;
			} else if (state == 120) {
				type = char_type;
			} else if (state == 121) {
				type = opening_bracket;
			} else if (state == 122) {
				type = closing_bracket;
			} else if (state == 123) {
				type = opening_c_bracket;
			} else if (state == 124) {
				type = closing_c_bracket;
			} else if (state == 125) {
				type = closing_s_bracket;
			} else if (state == 126) {
				type = opening_s_bracket;
			} else if (state == 127) {
				type = assignment;
			} else if (state == 128) {
				type = selector;
			} else if (state == 129) {
				type = mod_operator;
			} else if (state == 130) {
				type = semicolon;
			} else if (state == 131) {
				type = colon;
			} else {
				printf("Not implemented, state %d", state);
			}
			token_array_add(arr, type, token_index);
			symbol_table_add(table, token_index, position - token_len, line, cur - token_len, token_len);
			token_index++;
			token_len = 0;
			state = 0;
		} else if (state > 199) {
			if (state == 200) {
				int i = 1;
			} else if (state == 201) {
				line++;
			}
		} else if (state > 299) {
			token_len++;
		}
		position++;
	}
	

}
