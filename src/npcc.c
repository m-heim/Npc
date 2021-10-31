#include <stdio.h>
#include <stdlib.h>
#include "npcc.h"
#include "parser.h"

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
	printf("%s\n", read_program(fp));
	return 0;
	
	
}
char *read_program(FILE *fp) {
	// determine file size
	fseek(fp, 0L, SEEK_END);
	size_t size = ftell(fp);
	rewind(fp);
	
	char *code = malloc((1 + size) * sizeof(char));
	size_t pos = 0;
	while ((code[pos] = fgetc(fp)) != EOF) {
		pos++;
	}
	
	return code;
}
