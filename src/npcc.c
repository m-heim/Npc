#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "npcc.h"
#include "parser.h"
#include "scanner.h"

int main(int argc, char **argv) {
	char *file = argv[1];
	if (argc <= 1) {
		printf("Please provide a program to compilate\n");
		return 2;
	}
	FILE *fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Failed to open file %s, exit\n", file);
		return 2;
	}
	scanner_result result = lex(read_program(fp));
	int i;
	for(i = 0; i < result.node_array->used; i++) {
		printf("%s\n", node_type_get_canonial(node_array_get_node_type(result.node_array, i)));
	}
	printf("Parsing\n");
	ast *tree = parse_program(result);
	print_tree(tree, 0);

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
