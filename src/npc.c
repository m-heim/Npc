#include "npc.h"
#include "log.h"
#include "token.h"
#include "parser.h"
#include "scanner.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main_debug = 0;
int export_symbol = 0;
int export_tree = 0;
int lexer_debug = 0;
int parser_debug = 0;
int ir_debug = 0;
int main(int argc, char **argv) {
	if (argc <= 1) {
		printf("Please provide a program to compilate\n");
		return 2;
	}
	char *file = argv[argc - 1];
	FILE *fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Failed to open file %s, exit\n", file);
		return 2;
	}
	// set debug flag
	for (int i = 1; i <= argc - 1; i++) {
		if (strcmp(argv[i], "-d") == 0) {
			main_debug = 1;
		}
		if (strcmp(argv[i], "--export-symbol") == 0) {
			export_symbol = 1;
		}
		if (strcmp(argv[i], "--export-tree") == 0) {
			export_tree = 1;
		}
		if (strcmp(argv[i], "--lexer-debug") == 0) {
			lexer_debug = 1;
		}
		if (strcmp(argv[i], "--ir-debug") == 0) {
			lexer_debug = 1;
		}
	}
	scanner_result lexer_result = lex(read_program(fp), lexer_debug || main_debug, export_tree);
	if (main_debug) {
		printf("Pos\tType\n");
		for (int i = 0; i < lexer_result.token_array->used; i++) {
			printf("%d, %s\n", i,
				   token_type_get_canonial(
					   token_array_get_token_type(lexer_result.token_array, i)));
		}
		printf("Position,\tline\tval\n");
	}
	parser_result *parser_res = parse_program(lexer_result, main_debug || parser_debug);
	return 0;
}
char *read_program(FILE *fp) {
	// determine file size
	fseek(fp, 0L, SEEK_END);
	size_t size = ftell(fp);
	rewind(fp);

	char *code = malloc((size + 1) * sizeof(char));
	size_t pos = 0;
	while (pos != size) {
		code[pos] = fgetc(fp);
		pos++;
	}

	return code;
}
