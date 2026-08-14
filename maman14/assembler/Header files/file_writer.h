#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include "../Header files/symbol_table.h"
#include "../Header files/extern_usage.h"

/**
 * Generates the .ob, .ent, and .ext output files if the assembly was successful.
 * 
 * @param base_file_name The name of the file without extensions (e.g., "myprog").
 * @param ICF The final Instruction Counter value (size of code image).
 * @param DCF The final Data Counter value (size of data image).
 * @param instruction_image The fully resolved instruction memory image.
 * @param data_image The fully resolved data memory image.
 * @param sym_head The symbol table (used to generate .ent file).
 * @param ext_head The external usage list (used to generate .ext file).
 * @return TRUE if all files were created successfully, FALSE otherwise.
 */
int generate_output_files(const char *base_file_name, int ICF, int DCF, unsigned char instruction_image[], unsigned char data_image[], SymbolNode *sym_head, ExternUsageNode *ext_head);

#endif