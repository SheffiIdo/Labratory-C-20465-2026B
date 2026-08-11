#ifndef PARSER_H
#define PARSER_H

#include "../Header files/globals.h"
#include "../Header files/errors.h"

/**
 * Looks up an instruction by its exact name without using global variables.
 * @param name The string name of the instruction.
 * @param inst Pointer to an InstructionDef struct to populate if found.
 * @return TRUE if the instruction exists, FALSE otherwise.
 */
int get_instruction(const char *name, InstructionDef *inst);

/**
 * Checks if a string is a valid label format.
 * Must start with a letter, contain ONLY letters and digits, and respect MAX_LABEL_LENGTH.
 * @param word The string to check (without the trailing colon).
 * @return TRUE if valid, FALSE otherwise.
 */
int is_valid_label(const char *word);

/**
 * Extracts the next word (token) from a given line until a space, tab, comma, or newline is reached.
 * @param line The current position in the line string.
 * @param word Buffer array to store the extracted word.
 * @return Pointer to the next character in the line immediately after the extracted word.
 */
char *get_next_token(char *line, char *word);

/**
 * Parses a string to determine if it is a valid register.
 * @param operand The string to check (e.g., "$5").
 * @param reg_num Pointer to store the extracted register number (0-31).
 * @return TRUE if valid, FALSE otherwise.
 */
int parse_register(const char *operand, int *reg_num);

/**
 * Parses a string to determine if it is a valid 16-bit immediate integer.
 * @param operand The string to check (e.g., "-15").
 * @param immed Pointer to store the extracted integer.
 * @return TRUE if valid, FALSE otherwise.
 */
int parse_immediate(const char *operand, long *immed);

/**
 * Extracts comma-separated operands from a line into a 2D array.
 * Validates all comma rules (no leading, trailing, or consecutive commas).
 *
 * @param line_ptr The current reading pointer of the line.
 * @param operands A 2D array to store the extracted operand strings.
 * @param operand_count Pointer to an integer to store how many operands were found.
 * @param err_loc Location struct for printing exact errors.
 * @return TRUE if the syntax is valid, FALSE if a formatting error was found.
 */
int extract_operands(char *line_ptr, char operands[][MAX_LINE_LENGTH], int *operand_count, location err_loc);

#endif