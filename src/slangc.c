#include <stdio.h>
#include <stdlib.h>
#include "slangc.h"


int main(int argc, char **argv) {
	char *file = argv[1];
	if (argc <= 1) {
		printf("Please provide a program to compilate\n");
		return 2;
	}
	read_program(file);
	return 0;
	
	
}
char *read_program(char *filename) {
	// determine file size
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Failed to open file %s, exit\n", filename);
		exit(2);
	}
	fseek(fp, 0L, SEEK_END);
	size_t size = ftell(fp);
	rewind(fp);
	printf("Size is %d\n", size);
	return "Hello";

}
