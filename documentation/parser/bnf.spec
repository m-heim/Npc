// Classes of t
unop 		::= ! | ++ | --
binop 		::= + | - | * | / | ** | %  | < | <= | > | >=
assignment	::= += | -= | *= | /= | =
type_token      ::= "float" | "int" | "char" | "string"
string_literal  ::= \"[[:any:]]*\"
char_literal    ::= '[[:any:]]'
int_literal     ::= [0-9]+
float_literal   ::= [0-9]+.[0-9]+
bool_literal    ::= "true" | "false"
literal         ::= <string_literal> | <char_literal> | <int_literal> | <float_literal> | <bool_literal>
module_directive_token	::= "#MODULE"
program_directive_token	::= "#PROGRAM"
include_directive_token	::= "#using"
macro_directive_token	::= "#macro"
identifier_token	::= [A-z_][a-Z_0-9]*



// Types of source
program			    ::= <program_directive> <secondary_directive_list>? <functions>
program_directive	::= <program_directive_token> <identifier_token> ;
module_directive    ::= <module_directive_token> <identifier_token> ;
module			    ::= <module_directive> <secondary_directive_list>? <functions>
module_subselect	::= <identifier> . <module_subselect> | <identifier>

secondary_directive_list::= secondary_directive secondary_directive_list | secondary_directive
secondary_directive	::= include_directive | macro_directive

include_directive   ::= <include_directive_token> <module_subselect> <semicolon_token>
include_directive_list	::= include_directive include_directive_list | include_directive

macro_directive		::= macro_directive_token identifier literal
macro_directive_list::= macro_directive macro_directive_list | macro_directive


// Functions and procedures
function		    ::= <identifier_token> (<parameter_list>):<type> {statement}
functions		    ::= function functions | function

type                ::= <type_token> {[]}
declaration     	::= <type> <identifier> ; | <type> <assignment_expression> ;

expression          ::= <assignment_expression>
assignment_expressio::= <identifier> <assignment_operator> <conditional_expression> | <conditional_expression>
conditional_expression::= <logical-or-expression> | <logical-or-expression> ? <assignment_expression> 
logical-or-expression::= <logical-and-expression> | <logical-or-expression>
factor          	::= <unop> <factor> | <var> "++" | <var> "--" | "(" <exp> ")" | <float_literal> | <string_literal> | <char_literal> | <int_literal> | <bool_literal> | <var> | <function_call>
term            	::= <factor> "*" <term> | <factor> "/" <term> | <factor>
simple_exp             	::= <term> "+" <exp> | <term> "-" <exp> | <term>

var			        ::= <identifier> | <identifier> "[" <exp> "]"
function_call		::= <identifier> "(" <argument_list> ")"

parameter		    ::= <type> <identifier>
parameter_list		::= <parameter> , <parameter_list> | <parameter>

argument		    ::= <exp>
argument_list		::= <argument> "," <argument_list> | <argument>

continue_statement	::= "continue" ";"
break_statement		::= "break" ";"
return_statement	::= "return" ; | "return" <expression> ;
while_statement		::= "while" "(" <expression> ")" <block> ;
for_statement		::= for ( <expression> ; <expression> ; <expression> ) { <statement> } ;
if_statement		::= if ( <expression> ) { <statement> } ;

statement           ::= <continue_statement> | <break_statement> | <return_statement> |
                    ::= | <while_statement> | <for_statement> | <if_statement> |
                    ::= <declaration>

block               ::= "{" <statement> "}"