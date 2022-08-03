#include "scanner.h"
#include "char_utils.h"
#include "log.h"
#include "symbol_table.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lexing_error(size_t position, size_t line, char *code, size_t length) {
	char *red_on = "\033[0;31m";
	char *red_off = "\033[0m";
	char format[1024];
	char message[1024];
	sprintf(format,
			"{Lex} - on char %%lu in line %%ld\n%%.10s%s%%.%lds%s%%.%lds\n",
			red_on, length, red_off, 10 - length);
	sprintf(message, format, position, line, code - 10, code, code + length);
	size_t len = strlen(message);
	npc_log(log_bad, message);
	exit(1);
}

scanner_result lex(char *code, int debug, int export_symbol) {
	symbol_table *table = symbol_table_make();
	token_array *arr = token_array_make();

	scanner_result result;
	result.table = table;
	result.token_array = arr;

	// current position in stream
	size_t position = 0;
	// start of current token
	size_t start_position = 0;
	// length of lexeme
	size_t len = 0;

	// curr char
	char *cur = code;
	// start char of c
	char *start = code;

	int state = 0;
	size_t line = 0;
	npc_debug_log(debug, "{Lex} - now lexing.");
	char outputbuf[100];
	size_t token_index = 0;
	// is a hack to prevent it from stopping to scanning when we found the #end token
	while (state != 0 || *(code + position) != '\0') {
		cur = code + position;
		token_index = arr->used;
		sprintf(outputbuf, "{char=%c|state=%d}", *cur, state);
		npc_debug_log(debug, outputbuf);
		// if we arent in any specific state rn
		if (state == 0) {
			// if starts with latin or underscore is identifier
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
			} else if (*cur == ',') {
				state = 133;
			} else {
				npc_log(log_bad, "Unknown start of token");
				lexing_error(start_position, line, start,
							 position - start_position + 1);
			}
			// if we have an identifier we can have latin underscore or a number
		} else if (state == 1) {
			if (is_latin(cur) || is_underscore(cur) || is_number(cur)) {
				state = 1;
			} else {
				state = 100;
			}
			// plus
		} else if (state == 4) {
			if (*cur == '=') {
				state = 102;
			} else if (*cur == '+') {
				state = 104;
			} else if (is_number(cur)) {
				state = 5;
			} else {
				state = 103;
			}
			// minus
		} else if (state == 3) {
			if (*cur == '-') {
				state = 107;
			} else if (*cur == '=') {
				state = 106;
			} else if (is_number(cur)) {
				state = 5;
			} else {
				state = 108;
			}
			// str
		} else if (state == 41) {
			if (*cur == '"') {
				state = 119;
			} else if (*cur == '\\') {
				state = 42;
			} else {
				state = 41;
			}
			// str
		} else if (state == 42) {
			state = 41;
			// ?/
		} else if (state == 43) {
			if (is_latin(cur)) {
				state = 43;
			} else {
				state = 132;
			}
		} else if (state == 38) {
			if (*cur == '\'') {
				npc_log(log_bad, "Empty char not allowed");
				lexing_error(start_position, line, start,
							 position - start_position + 1);
			} else if (*cur == '\\') {
				state = 44;
			} else {
				state = 39;
			}
		} else if (state == 44) {
			if (*cur == 'n' || *cur == 'b' || *cur == 't' || *cur == 'r' ||
				*cur == 'f' || *cur == '\'' || *cur == '\\') {
				state = 39;
			} else {
				npc_log(log_bad, "Unknown escape");
				lexing_error(start_position, line, start,
							 position - start_position + 1);
			}
		} else if (state == 39) {
			if (*cur == '\'') {
				state = 120;
			} else {
				lexing_error(start_position, line, start,
							 position - start_position + 1);
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
			token_type ntype;
			token_type_class type_class;
			// We have an identifier
			if (state == 100) {
				position--;
				len = position - start_position + 1;
				if (len == 2 && strncmp(start, "if", len) == 0) {
					ntype = if_keyword_token;
					type_class = keyword_c;
				} else if (len == 3 && strncmp(start, "for", len) == 0) {
					ntype = for_keyword_token;
					type_class = keyword_c;
				} else if (len == 5 && strncmp(start, "while", len) == 0) {
					ntype = while_keyword_token;
					type_class = keyword_c;
				} else if (len == 4 && strncmp(start, "else", len) == 0) {
					ntype = else_keyword_token;
					type_class = keyword_c;
				} else if (len == 6 && strncmp(start, "return", len) == 0) {
					ntype = return_keyword_token;
					type_class = keyword_c;
				} else if (len == 8 && strncmp(start, "continue", len) == 0) {
					ntype = continue_keyword_token;
					type_class = keyword_c;
				} else if (len == 5 && strncmp(start, "break", len) == 0) {
					ntype = break_keyword_token;
					type_class = keyword_c;
				} else {
					ntype = identifier_token;
					type_class = nac_c;
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
				ntype = int_literal_token;
				position--;
				type_class = literal_c;
			} else if (state == 101) {
				position--;
				ntype = float_literal_token;
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
				type_class = relop_c;
				position--;
			} else if (state == 110) {
				ntype = ge_operator_token;
				type_class = relop_c;
			} else if (state == 111) {
				ntype = lt_operator_token;
				type_class = relop_c;
				position--;
			} else if (state == 112) {
				ntype = le_operator_token;
				type_class = relop_c;
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
				ntype = string_literal_token;
				type_class = literal_c;
			} else if (state == 120) {
				ntype = char_literal_token;
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
				// directive
				position--;
				len = position - start_position + 1;
				if (len == 8 && strncmp(start, "#PROGRAM", len) == 0) {
					ntype = program_directive_token;
					type_class = prim_directive_c;
				} else if (len == 7 && strncmp(start, "#MODULE", len) == 0) {
					ntype = module_directive_token;
					type_class = prim_directive_c;
				} else if (len == 6 && strncmp(start, "#using", len) == 0) {
					ntype = include_directive_token;
					type_class = sec_directive_c;
				} else if (len == 6 && strncmp(start, "#macro", len) == 0) {
					ntype = macro_directive_token;
					type_class = sec_directive_c;
				} else if (len == 4 && strncmp(start, "#END", len) == 0) {
					ntype = end_directive_token;
					type_class = prim_directive_c;
				} else {
					npc_log(log_bad, "Not a valid directive");
					lexing_error(start_position, line, start,
								 position - start_position + 1);
				}
			} else if (state == 133) {
				ntype = comma_token;
				type_class = punctuation_c;
			} else {
				npc_log(log_intern, "Not implemented, state");
				lexing_error(start_position, line, start,
							 position - start_position + 1);
			}
			// re set cur because we did position-- above;
			cur = code + position;
			// get length of the token
			len = cur - start + 1;

			token_array_add(arr, ntype, type_class, start_position);
			if (debug != 0) {
				sprintf(outputbuf, "Added %s", token_type_get_canonial(ntype));
				npc_debug_log(debug, outputbuf);
			}
			if (ntype == identifier_token || type_class == literal_c) {
				symbol_table_add(table, start_position, line, start, len);
			}
			token_index++;
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
			} else {
				lexing_error(start_position, line, start,
							 position - start_position + 1);
			}
			start = cur + 1;
			start_position = position + 1;
		} else if (state > 299) {
			npc_log(log_intern, "Not implemented state");
		}
		position++;
	}
	npc_debug_log(debug, "{Lex} - done lexing.");
	if (export_symbol != 0) {
		FILE *file = fopen("symbol_table.exp", "w");
		write_symbol_table(file, result.table);
		fclose(file);
	}
	if (debug != 0) {
		printf("--------Start of symbol table--------\n");
		write_symbol_table(stdout, result.table);
		printf("--------End of symbol table--------\n");
	}
	if (debug != 0) {
		printf("--------Start of tokens--------\n");
		print_tokens(result.token_array);
		printf("--------End of tokens--------\n");
	}
	return result;
}
