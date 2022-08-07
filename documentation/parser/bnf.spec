#tokens
// arith
plus_token              ::= "+"
minus_token             ::= "-"
mul_token               ::= "*"
div_token               ::= "/"
not_token               ::= "!"
inc_token               ::= "++"
dec_token               ::= "--"

// rel
lower_than_token        ::= "<"
greater_than_token      ::= ">"
greater_equal_token     ::= ">="
lower_equal_token       ::= "<="

// assignment
assignment_token        ::= "="
assignment_plus_token   ::= "+="
assignment_minus_token  ::= "-="
assignment_mul_token    ::= "*="
assignment_div_token    ::= "/="

// literals
string_literal_token    ::= ""[[:any:]]*""
char_literal_token      ::= "'[[:any:]]'"
int_literal_token       ::= "[+-][0-9]+"
long_literal_token       ::= "[+-][0-9]+"
float_literal_token     ::= "[+-][0-9]+.[0-9]+"
double_literal_token    ::= "[+-][0-9]+.[0-9]+"
bool_literal_token      ::= "none"
// directives
module_directive_token	::= "#MODULE"
program_directive_token	::= "#PROGRAM"
include_directive_token	::= "#using"
macro_directive_token	::= "#macro"

// other
identifier_token	    ::= "[A-z_][a-Z_0-9]+"
equals_token            ::= "=="
does_not_equal_token    ::= "!="


// keywords
break_token             ::= "break"
continue_token          ::= "continue"
return_token            ::= "return"
if_token                ::= "if"
for_token               ::= "for"
while_token             ::= "while"
else_token              ::= "else"

// structure
open_s_bracket_token    ::= "["
closing_s_bracket_token ::= "]"
open_bracket_token      ::= "("
closing_bracket_token   ::= ")"
open_c_bracket_token    ::= "{"
closing_c_bracket_token ::= "}"
dot_token               ::= "."
semicolon_token         ::= ";"
comma_token             ::= ","
questionmark_token      ::= "?"
#endtokens

#productions
// classes
assignment_operator     ::= <assignment_token> | <assignment_mul_token> | <assignment_div_token> | <assignment_minus_token> | <assignment_plus_token>
unop                    ::= <not_token> | <inc_token> | <dec_token>
relop                   ::= <lower_than_token> | <greater_than_token> | <greater_equal_token> | <lower_equal_token>
literal                 ::= <int_literal_token> | <bool_literal_token> | <float_literal_token> | <string_literal_token> | <long_literal_token> | <double_literal_token>
// Types of source
program			        ::= <program_directive> <secondary_directive_list> <functions> | <program_directive> <functions>
program_directive	    ::= <program_directive_token> <identifier_token>

module_directive        ::= <module_directive_token> <identifier_token>
module			        ::= <module_directive> <secondary_directive_list> <functions>
module_subselect	    ::= <identifier_token> <dot_token> <module_subselect> | <identifier_token>

secondary_directive_list::= <secondary_directive> <secondary_directive_list>
secondary_directive	    ::= <include_directive> | <macro_directive>

include_directive       ::= <include_directive_token> <module_subselect>
include_directive_list	::= <include_directive> <include_directive_list> | <include_directive>

macro_directive		    ::= <macro_directive_token> <identifier_token> <expression>
macro_directive_list    ::= <macro_directive> <macro_directive_list> | <macro_directive>


// Functions and procedures
function		        ::= <type> <identifier_token> <open_bracket_token> <parameter_list> <closing_bracket_token> <block> | <type> <identifier_token> <open_bracket_token> <closing_bracket_token> <block>
functions		        ::= <function> <functions> | <function>

type                    ::= <identifier_token> <dims> | <identifier_token>
dim                     ::= <open_s_bracket_token> <closing_s_bracket_token>
dims                    ::= <dim> <dims>
declaration     	    ::= <type> <identifier_token> <assignment_token> <semicolon_token> | <type> <identifier_token> <assignment_token> <expression> <semicolon_token>

expression_statement        ::= <expression> <semicolon_token>
expression                  ::= <literal>
//assignment_expressio    ::= <identifier> <assignment_operator> <conditional_expression> | <conditional_expression>
//conditional_expression  ::= <logical-or-expression> | <logical-or-expression> ? <assignment_expression> 
//logical-or-expression   ::= <logical-and-expression> | <logical-and-expression> || <logical-or-expression>
//logical-and-expression  ::= <equality-expression> | <logical-and-expression> && <equality-expression>
//equality-expression     ::= <additive-expression> | <additive-expression> + <equality-expression> | <additive-expression> - <equality-expression>
//multiplicative-expression::= <unary-expression> | <unary-expression> * <multiplicative-expression> | <unary-expression> * <multiplicative-expression> | <unary-expression> % <multiplicative-expression>

parameter		        ::= <type> <identifier_token>
parameter_list		    ::= <parameter> <comma_token> <parameter_list> | <parameter>

argument		        ::= <expression>
argument_list		    ::= <argument> <comma_token> <argument_list> | <argument>

continue_statement	    ::= <continue_token> <semicolon_token>
break_statement		    ::= <break_token> <semicolon_token>
return_statement	    ::= <return_token> <semicolon_token> | <return_token> <expression> <semicolon_token>
while_statement		    ::= <while_token> <open_bracket_token> <expression> <closing_bracket_token> <block>
for_statement		    ::= <for_token> <open_bracket_token> <expression> <semicolon_token> <expression> <semicolon_token> <expression> <closing_bracket_token> <block>
if_statement		    ::= <if_token> <open_bracket_token> <expression> <closing_bracket_token> <block>

statement               ::= <continue_statement> | <break_statement> | <return_statement> | <while_statement> | <for_statement> | <if_statement> | <expression_statement> | <declaration>
statements              ::= <statement> <statements> | <statement>
block                   ::= <open_c_bracket_token> <statements> <closing_c_bracket_token>

#endproductions