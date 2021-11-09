unop 			::= ! | ++ | --
binop 			::= + | - | * | / | ** | % | += | -= | *= | /= | < | <= | > | >=
type            ::= float | int | char | string

program			::= <program_directive> <secondary_directive_list>? <main_function> <functions>
module			::= <module_directive> <secondary_directive_list> <functions>
function		::= <function_token> <identifier> (parameter_list):<type> {statement}
functions		::= function functions | function

compound_statement	::= <statement> <compound_statement> | <statement>
exp			    ::= false | true | int_type 
parameter		::= <identifier> <identifier>
parameter_list		::= <parameter> , <parameter_list> | <parameter>

continue_statement	::= continue ;
break_statement		::= break;
return_statement	::= "return" ; | "return" <expression> ;
while_statement		::= while ( <expression> ) { <statement> } ;
for_statement		::= for ( <expression> ; <expression> ; <expression> ) { <statement> } ;
if_statement		::= if ( <expression> ) { <statement> } ;

// DIRECTIVES
module_directive	::= module_directive_token identifier
program_directive	::= program_directive_token identifier
include_directive	::= include_directive_token module_subselect

secondary_directive_list::= secondary_directive secondary_directive_list | secondary_directive
secondary_directive	::= include_directive | macro_directive
include_directive_list	::= include_directive include_directive_list | include_directive
macro_directive		::= macro_directive_token identifier literal
directive_block		::=
directive		::= include_directive

// Tokens
module_directive_token	::= #MODULE
program_directive_token	::= #PROGRAM
include_directive_token	::= #using
macro_directive_token	::= #macro
identifier_token	::= [A-z_][a-Z_0-9]*
main_identifier_token	::= main
function_token          ::= fun

module_subselect	::= <identifier> . <module_subselect> | <identifier>
