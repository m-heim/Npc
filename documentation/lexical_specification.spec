e = epsilon = ""

identifier=		[0-9A-Za-z_][0-9A-Za-z_]*
integer=		(+|-|e)[0-9][0-9]*
float=			(+|-|e)[0-9]*.[0-9][0-9]*

char_literal=		'[[:any:]]'
string_literal=		"[[:any:]]*"

assignment_op=		=
gt_op=			>
ge_op=			>=
lt_op=			<
le_op=			<=
selector=		.

add_op=			+
sub_op=			-
div_op=			/
mul_op=			*
pot_op= 		**
modulus_op=		%
add_dir_op=		+=
sub_dir_op=		-=

inc_op=			++
dev_op=			--

open_bracket=		(
closing_bracket=	)

open_c_bracket=		{
closing_c_bracket=	}

open_s_bracket=		[
closing_s_bracket=	]
