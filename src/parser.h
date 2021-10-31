#ifndef PARSER_H
#define PARSER_H

#include "token_tree.h"

token_tree *parse_program(token *tokens, unsigned long len);

#endif
