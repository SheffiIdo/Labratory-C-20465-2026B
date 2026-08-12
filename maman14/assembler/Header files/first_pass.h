#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "../Header files/symbol_table.h"

/**
 * Executes the First Pass algorithm on the provided assembly source file.
 * Builds the Symbol Table, translates instructions and data into memory arrays,
 * and calculates the initial memory footprint.
 *
 * @param file_name The name of the expanded source file (e.g., "prog.am").
 * @param head Pointer to the head of the Symbol Table linked list.
 * @param instruction_image Array to store the encoded machine instructions.
 * @param data_image Array to store the encoded data directives (.db, .asciz, etc.).
 * @param IC Pointer to the Instruction Counter to track code memory usage.
 * @param DC Pointer to the Data Counter to track data memory usage.
 * @return TRUE if the pass completed without errors, FALSE if errors were found.
 */
int execute_first_pass(const char *file_name, SymbolNode **head, unsigned char instruction_image[], unsigned char data_image[], int *IC, int *DC);

#endif