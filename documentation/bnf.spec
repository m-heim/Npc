// Classes of t
unop 		::= ! | ++ | --
binop 		::= + | - | * | / | ** | %  | < | <= | > | >=
assignment	::= += | -= | *= | /= | = 
type            ::= "float" | "int" | "char" | "string"
string_literal  ::= \"[[:any:]]*\"
char_literal    ::= '[[:any:]]'
int_literal     ::= [0-9]+
float_literal   ::= [0-9]+.[0-9]+
bool_literal    ::= "true" | "false"
literal         ::= <string_literal> | <char_literal> | <int_literal> | <float_literal> | <bool_literal>



// Types of source
# nullable(program) = False, First = {<program_directive>}
program			::= <program_directive> <secondary_directive_list>? <functions>

# nullable(program) = False, First = {<module_directive>}
module			::= <module_directive> <secondary_directive_list>? <functions>


// Functions and procedures
# nullable(function) = False, First = {<function_token>}
function		::= <identifier_token> (<parameter_list>):<type> {statement}

# nullable(functions) = False, First = {<function_token>}
functions		::= function functions | function

# nullable(declaration) = False, First = {<float_token>, <string_token>, <char_token>, <int_token>}
declaration     	::= <type> <identifier> <semicolon_token> | <type> <identifier> <assignment_token> <exp> <semicolon_token>

# nullable(var) = False, First = {<identifier>}
var			::= <identifier> | <identifier> "[" <exp> "]"
# nullable(factor) = False, First = 1. {"++", "--", "!"} 2/3. {<identifier>} 4. {"("} 5/6/7/9/10. {<literal>} 11. {<identifier>} 12. {<identifier>}
factor          	::= <unop> <factor> | <var> "++" | <var> "--" | "(" <exp> ")" | <float_literal> | <string_literal> | <char_literal> | <int_literal> | <bool_literal> | <var> | <function_call>
# nullable(term) = False, First = First(factor)
term            	::= <factor> "*" <term> | <factor> "/" <term> | <factor>
# nullable(exp) = False, First = First(factor)
simple_exp             	::= <term> "+" <exp> | <term> "-" <exp> | <term>
expression          ::= <simple_exp> | <simple_exp> <relop> <simple_exp>
function_call		::= <identifier> "(" <argument_list> ")"

parameter		::= <identifier> <identifier>
parameter_list		::= <parameter> , <parameter_list> | <parameter>

argument		::= <exp>

argument_list		::= <argument> "," <argument_list> | <argument>

continue_statement	::= continue ;
break_statement		::= break;
return_statement	::= "return" ; | "return" <expression> ;
while_statement		::= while ( <expression> ) { <statement> } ;
for_statement		::= for ( <expression> ; <expression> ; <expression> ) { <statement> } ;
if_statement		::= if ( <expression> ) { <statement> } ;


// DIRECTIVES
program_directive	::= <program_directive_token> <identifier_token> <semicolon_token>

module_directive    ::= <module_directive_token> <identifier_token> <semicolon_token>

secondary_directive_list::= secondary_directive secondary_directive_list | secondary_directive
secondary_directive	::= include_directive | macro_directive

# nullable(module_subselect) = False, First = {<identifier>}
module_subselect	::= <identifier> . <module_subselect> | <identifier>

include_directive   ::= <include_directive_token> <module_subselect> <semicolon_token>
include_directive_list	::= include_directive include_directive_list | include_directive

macro_directive		::= macro_directive_token identifier literal
macro_directive_list::= macro_directive macro_directive_list | macro_directive


// Tokens
module_directive_token	::= "#MODULE"
program_directive_token	::= "#PROGRAM"
include_directive_token	::= "#using"
macro_directive_token	::= "#macro"
identifier_token	::= [A-z_][a-Z_0-9]*
main_identifier_token	::= "main"
function_token          ::= "fun"
semicolon_token         ::= ;

