#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "../Header files/symbol_table.h"
#include "../Header files/extern_usage.h"

/**
 * Executes the second pass of the assembler.
 * Resolves unknown symbol addresses, calculates branch distances,
 * marks .entry symbols, and tracks .extern usage.
 *
 * @param file_name The original source file name.
 * @param head Pointer to the head of the symbol table.
 * @param ext_head Pointer to the head of the external usage tracking list.
 * @param instruction_image The partially completed instruction memory image.
 * @param IC Pointer to the Instruction Counter (used for distance calculation).
 * @return TRUE if the pass completed without errors, FALSE otherwise.
 */
int execute_second_pass(const char *file_name, SymbolNode *head, ExternUsageNode **ext_head, unsigned char instruction_image[], int *IC);

#endif