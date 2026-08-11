#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "../Header files/symbol_table.h"

/**
 * Executes the First Pass algorithm on the provided assembly source file.
 * Builds the Symbol Table and calculates the initial memory footprint.
 *
 * @param filename The name of the expanded source file (e.g., "prog.am").
 * @param head Pointer to the head of the Symbol Table linked list.
 * @return TRUE if the pass completed without errors, FALSE if errors were found.
 */
int execute_first_pass(const char *filename, SymbolNode **head);

#endif