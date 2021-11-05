#include "token.h"
#include "scanner.h"
#include "symbol_table.h"
#include <stdlib.h>

token *lex(char *code) {
	symbol_table *table = symbol_table_make();
	token_array *arr = token_array_make();
	scanner_result result;
	result.table = table;
	result.tkn_array = arr;

	size_t position = 0;
	char *cur;
	int state = 0;
	size_t line = 0;


	while (code + position != '\0') {
		if (state == 0) {
			if (*cur == ' ') {
				
			} else if (*cur == '\n') {
			
			} else if () {
				state = 1;
			}
		} else if (state == 1) {
			if ((*cur >= 65 && *cur <= 90) || (*cur >= 97 && *cur <= 122) || (*cur >= 48 && *cur <=57) || *cur == 95) {
				state = 1;
			} else {
				state = 2;
			}
		}
	}
	

}
