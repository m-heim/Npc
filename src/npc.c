#include "npc.h"
#include "log.h"
#include "node.h"
#include "parser.h"
#include "scanner.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main_debug = 1;
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
	}
	npc_debug_log(main_debug, "Scanning now...");
	scanner_result lexer_result = lex(read_program(fp), main_debug);
	if (main_debug) {
		printf("Pos\tType\n");
		for (int i = 0; i < lexer_result.node_array->used; i++) {
			printf("%d, %s\n", i,
				   node_type_get_canonial(
					   node_array_get_node_type(lexer_result.node_array, i)));
		}
		printf("Position,\tline\tval\n");
		print_symbol_table((lexer_result.table));
	}
	printf("Parsing\n");
	parser_result parser_res = parse_program(lexer_result);
	print_tree(parser_res.tree, 0);
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
