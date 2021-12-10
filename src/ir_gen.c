#include "ir_gen.h"
#include "ast.h"
#include "node.h"
#include "three_address_code.h"
#include "typetable.h"
#include <string.h>
#include <stdio.h>
v_table *v_table_make() {
    v_table *table = malloc(sizeof(v_table));
    table->name = malloc(sizeof(char *) * V_TABLE_INIT_SIZE);
    table->used = 0;
    table->size = V_TABLE_INIT_SIZE;
    return table;
}

size_t v_table_add(v_table *table, const char *str) {
    if (table->size == table->used) {
        table->name = realloc(table->name, table->size * 2 * sizeof(char *));
        table->size *= 2;
    }
    table->name[table->used] = malloc((1 + strlen(str)));
    strcpy(table->name[table->used], str);
    return table->used ++;
}

const char * v_table_get(v_table *table, size_t id) {
    if(id >= table->used) {
        printf("IR_GEN: undefined error in ir generation. Programm will end.");
        _Exit(1);
    }
    return table->name[id];
}

void ir_gen_err() {
	printf("IR_GEN: Undefined error in ir gen, program ends now");
	_Exit(1);
}

ir_gen_result generate(parser_result parser_out) {
    ir_gen_result result;
    result.table = v_table_make();
    result.code = three_address_code_make();
    ast *tree = parser_out.tree;
    symbol_table *table = parser_out.table;
    node *curr;
    while(1) {
        
    }
}

ir_gen_result *translate(ir_gen_result *i_result, ast *tree, symbol_table *table, long place) {
    switch (tree->n.type) {
        case function_n:
			three_address_code_add(i_result->code, MAXIMUM_LABEL, funheader, UNDEFINED, UNDEFINED, UNDEFINED);
			if (tree->children[2]->n.type == parameter_list_n) {
				long offset = 0;
				for(int i = 0; i < tree->children[2]->used; i ++) {
					three_address_code_add(i_result->code, MAXIMUM_LABEL, mem_copy_op, offset, typetable_get_size(typetable *table, int id), -offset)
					offset
				}
			}
		
		case expression_n:
            if (tree->used == 3) {
                long place1 = new_var();
                long place2 = new_var();
                translate(i_result, tree, table, place1);
                translate(i_result, tree, table, place2);
                three_address_code_add(i_result->code, MAXIMUM_LABEL, get_op(tree->children[1]->n.type), place, place1, place2);
            } else if (tree->used == 1) {
                long place1 = new_var();
                translate(i_result, tree, table, place1);
            } else {
                ir_gen_err();
            }
            break;
        case simple_expression_n:
            if(tree->used == 3) {
                long place1 = new_var();
                long place2 = new_var();
                translate(i_result, tree, table, place1);
                translate(i_result, tree, table, place2);
                three_address_code_add(i_result->code, MAXIMUM_LABEL, get_op(tree->children[1]->n.type), place, place1, place2);
            } else if (tree->used == 1) {
                long place1 = new_var();
                translate(i_result, tree, table, place1);
            } else {
                ir_gen_err();
            }
            break;
        case term_n:
            if(tree->used == 3) {
                long place1 = new_var();
                long place2 = new_var();
                translate(i_result, tree, table, place1);
                translate(i_result, tree, table, place2);
                three_address_code_add(i_result->code, MAXIMUM_LABEL, get_op(tree->children[1]->n.type), place, place1, place2);
            } else if (tree->used == 1) {
                long place1 = new_var();
                translate(i_result, tree, table, place1);
            } else {
                ir_gen_err();
            }
            break;
        case factor_n:
            if(tree->used == 3) {
                long place1 = new_var();
                translate(i_result, tree, table, place1);
                three_address_code_add(i_result->code, MAXIMUM_LABEL, get_op(tree->children[1]->n.type), place, place1, );
            } else if (tree->used == 1) {
                long place1 = new_var();
                translate(i_result, tree, table, place1);
            } else {
                ir_gen_err();
            }
            break;
        default:
    }
    }
}

three_address_code_op get_op(node_type type) {
	if (type == identifier_token) {
		return "identifier_token";
	} else if (type == assignment_token) {
		return "assignment_token";
	} else if (type == imm_plus_operator_token) {
		return "imm_plus_operator_token";
	} else if (type == imm_minus_operator_token) {
		return "imm_minus_operator_token";
	} else if (type == imm_mul_operator_token) {
		return "imm_mul_operator_token";
	} else if (type == imm_division_operator_token) {
		return "imm_division_operator_token";
	} else if (type == plus_operator_token) {
		return "plus_operator_token";
	} else if (type == minus_operator_token) {
		return "minus_operator_token";
	} else if (type == multiplication_operator_token) {
		return "multiplication_operator_token";
	} else if (type == division_operator_token) {
		return "division_operator_token";
	} else if (type == mod_operator_token) {
		return "mod_operator_token";
	} else if (type == pot_operator_token) {
		return "pot_operator_token";
	} else if (type == gt_operator_token) {
		return gt_op;
	} else if (type == lt_operator_token) {
		return lt_op;
	} else if (type == le_operator_token) {
		return le_op;
	} else if (type == ge_operator_token) {
		return ge_op;
	} else if (type == floor_div_operator_token) {
		return "floor_div_operator_token";
	} else if (type == decrement_operator_token) {
		return "decrement_operator_token";
	} else if (type == not_token) {
		return "not-token";
	} else if (type == increment_operator_token) {
		return "increment_operator_token";
	} else if (type == string_literal) {
		return "string_literal";
	} else if (type == char_literal) {
		return "char_literal";
	} else if (type == int_literal) {
		return "int_literal";
	} else if (type == float_literal) {
		return "float_literal";
	} else if (type == string_type_token) {
		return "string_type_token";
	} else if (type == char_type_token) {
		return "char_type_token";
	} else if (type == float_type_token) {
		return "float_type_token";
	} else if (type == int_type_token) {
		return "int_type_token";
	} else if (type == program_n) {
		return "program_n";
	} else if (type == module_n) {
		return "module_n";
	} else if (type == secondarydirective_n) {
		return "secondarydirective_n";
	} else if (type == secondarydirective_list_n) {
		return "secondarydirective_list_n";
	} else if (type == include_directive_n) {
		return "include_directive_n";
	} else if (type == include_directive_subselect_n) {
		return "include_directive_subselect_n";
	} else if (type == functions_n) {
		return "functions_n"; 
	} else if (type == program_directive_n) {
		return "program_directive_n";
	} else if (type == module_directive_n) {
		return "module_directive_n";
	} else if (type == macro_directive_n) {
		return "macro_directive_n";
	} else if (type == function_n) {
		return "function_n";
	} else if (type == unop_n) {
		return "unop_n";
	} else if (type == binop_n) {
		return "binop_n";
	} else if (type == parameter_n) {
		return "parameter_n";
	} else if (type == parameter_list_n) {
		return "parameter_list_n";
	} else if (type == type_n) {
		return "type_n";
	} else if (type == 	block_n) {
		return "block_n";	
	} else if (type == declaration_n) {
		return "declaration_n";	
	} else if (type == simple_expression_n) {
		return "simple_expression_n";	
	} else if (type == expression_n) {
		return "expression_n";	
	} else if (type == factor_n) {
		return "factor_n";	
	} else if (type == term_n) {
		return "term_n";	
	} else if (type == if_statement_n) {
		return "if_statement_n";
	} else if (type == statement_n) {
		return "statement_n";
	} else if (type == return_statement_n) {
		return "return_statement_n";
	} else if (type == for_statement_n) {
		return "for_statement_n";
	} else if (type == function_call_n) {
		return "fun_call_n";	
	} else if (type == argument_list_n) {
		return "argument_list_n";	
	} else if (type == argument_n) {
		return "argument_n";	
	} else if (type == return_keyword_token) {
		return "return_keyword_token";
	} else if (type == for_keyword_token) {
		return "for_keyword_token";
	} else if (type == if_keyword_token) {
		return "IF_keyword_token";
	} else {
		return "Tes";
	}
}

long new_var() {
    static long current;
    return current++;
}