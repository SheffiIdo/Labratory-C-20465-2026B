#ifndef UTILS_H
#define UTILS_H

#include "globals.h"

/**
 * Skips spaces and tabs at the start of a line and copies the remaining
 * characters into the output buffer.
 * 
 * @param output The buffer where the trimmed string will be stored.
 * @param input The original string to be trimmed.
 */
void trim_leading_whitespace(char *output, const char *input);

/**
 * Checks if a given string illegally uses a reserved assembly language keyword
 * (instructions, directives, or macro tokens).
 *
 * @param name The string identifier to check.
 * @return TRUE (1) if it is a reserved word, FALSE (0) if it is safe to use.
 */
int is_reserved_word(const char *name);

/**
 * Checks if a macro name is valid (starts with a letter, contains only alnum or '_')
 * @param name The macro name to validate
 * @return TRUE if valid, FALSE otherwise
 */
int is_valid_macro_name(const char *name);

#endif /* UTILS_H */