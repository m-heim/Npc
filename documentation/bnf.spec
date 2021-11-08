unop 		::= !
binop 		::= + | - | * | / | ** | % | += | -= | *= | /= | < | <= | > | >=
exp		::= false | true | int_type 
int_type	::= int | char | long
float_type	::= float
program		::= <program_directive> <secondary_directive_list> <main_function> <functions>

function	::= identifier identifier(parameters) {statement}
functions	::= function functions | function

compound_statement	::=	<statement> <compound_statement> | <statement>

jump_statement		::=	continue ; | break ; | return expression ;
while_statement		::=	while ( <expression> ) { <statement> } ;
for_statement		::=	for ( <expression> ; <expression> ; <expression> ) { <statement> } ;

if_statement		::=	if ( <expression> ) { <statement> } ;


module_directive::= module_directive_token identifier
program_directive	::= program_directive_token identifier
include_directive::= include_directive_token module_subselect

secondary_directive_list	::= secondary_directive secondary_directive_list | secondary_directive
secondary_directive	::= include_directive | macro_directive
include_directive_list	::= include_directive include_directive_list
macro_directive	::= macro_directive_token identifier literal
directive_block	::=
directive	::= include_directive


module_directive_token	::= #MODULE
program_directive_token	::= #PROGRAM
include_directive_token	::= #using
macro_directive_token	::= #macro
identifier_token	::= [A-z_][a-Z_0-9]*
main_identifier_token	::= main

module_subselect	::= identifier.module_subselect | identifier
