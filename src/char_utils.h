/**
 * @file char_utils.h
 * @author MaximilianHeim@protonmail.com
 * @brief An utility class for scanning, should be selfexplanatory.
 * @version 0.1
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H

// general purpose library useful for working with strings
int is_space(char *ptr);
int is_tab(char *ptr);
int is_whitespace(char *ptr);
int is_newline(char *ptr);
int is_latin(char *ptr);
int is_number(char *ptr);
int is_underscore(char *ptr);

#endif