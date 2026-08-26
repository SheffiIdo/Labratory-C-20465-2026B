#include "../Header files/second_pass.h"
#include "../Header files/parser.h"
#include "../Header files/utils.h"
#include "../Header files/errors.h"
#include "../Header files/globals.h"
#include "../Header files/symbol_table.h"
#include "../Header files/extern_usage.h"
#include <stdio.h>
#include <string.h>

/* --- Private Helper Function Declarations --- */
static void process_entry_directive(char *line_ptr, SymbolNode *head, location err_loc, int *error_flag);
static void complete_i_type_branch(char operands[][MAX_LINE_LENGTH], SymbolNode *head, unsigned char instruction_image[], int IC, location err_loc, int *error_flag);
static void complete_j_type_instruction(char operands[][MAX_LINE_LENGTH], SymbolNode *head, ExternUsageNode **ext_head, unsigned char instruction_image[], int IC, location err_loc, int *error_flag);

/* --- Main Second Pass Execution --- */
int execute_second_pass(const char *file_name, SymbolNode *head, ExternUsageNode **ext_head, unsigned char instruction_image[], int *IC) {
    FILE *file;
    char line[LINE_BUFFER_SIZE];
    int line_num = 0;
    int error_flag = FALSE;
    location err_loc;
    *IC = IC_INIT_VALUE;
    err_loc.file_name = (char *)file_name;

    file = fopen(file_name, "r");
    if (file == NULL) {
        print_internal_error(ERROR_CODE_2);
        return FALSE;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *ptr = line;
        char first_token[MAX_LINE_LENGTH] = {0};
        InstructionDef inst;
        int ch;
        line_num++;
        err_loc.line_num = line_num;

        /* Skip lines that exceed length (already flagged in Pass 1) */
        if (strchr(line, '\n') == NULL && !feof(file)) {
            while ((ch = fgetc(file)) != '\n' && ch != EOF);
            continue;
        }

        skip_whitespace(&ptr);

        /* Ignore empty lines and comments */
        if (*ptr == '\0' || *ptr == '\n' || *ptr == COMMENT_CHAR) {
            continue;
        }

        ptr = get_next_token(ptr, first_token);

        /* Ignore the label definition if one exists */
        if (strlen(first_token) > 0 && first_token[strlen(first_token) - 1] == ':') {
            ptr = get_next_token(ptr, first_token);
            if (strlen(first_token) == 0) {
                continue;
            }
        }

        /* Route Directives */
        if (first_token[0] == '.') {
            if (strcmp(first_token, ".entry") == STRING_MATCH) {
                process_entry_directive(ptr, head, err_loc, &error_flag);
            }
            continue;
        }

        /* Route Instructions */
        if (get_instruction(first_token, &inst) == TRUE) {
            char operands[MAX_OPERANDS][MAX_LINE_LENGTH] = {{0}};
            int op_count = 0;

            extract_operands(ptr, operands, &op_count, err_loc);

            if (inst.type == I_TYPE && inst.opcode >= MIN_BRANCH_OPCODE && inst.opcode <= MAX_BRANCH_OPCODE) {
                complete_i_type_branch(operands, head, instruction_image, *IC, err_loc, &error_flag);
            }
            else if (inst.type == J_TYPE && inst.opcode != STOP_OPCODE) {
                complete_j_type_instruction(operands, head, ext_head, instruction_image, *IC, err_loc, &error_flag);
            }

            (*IC) += BYTES_PER_INSTRUCTION;
        }
        /* Free and exit if allocation fails */
        if (memory_allocation_fail == TRUE) {
            fclose(file);                  /* Prevent file leak */
            free_symbol_table(head);       /* Prevent Symbol leak */
            free_extern_usage(*ext_head);  /* Prevent Extern leak */
            print_internal_error(ERROR_CODE_1); /* Exits safely */
        }
    }

    fclose(file);
    return (error_flag == FALSE);
}

/* --- Private Helper Implementations --- */

/*
 * Locates a symbol declared as .entry in the Symbol Table and flags it.
 * If the symbol was never defined in the file, it throws an error.
 */
static void process_entry_directive(char *line_ptr, SymbolNode *head, location err_loc, int *error_flag) {
    char entry_label[MAX_LINE_LENGTH] = {0};
    SymbolNode *sym;

    get_next_token(line_ptr, entry_label);
    sym = find_symbol(head, entry_label);

    if (sym == NULL) {
        print_external_error(ERROR_CODE_57, err_loc); /* Entry symbol not found */
        *error_flag = TRUE;
    }else if (sym->is_extern == TRUE) {
        print_external_error(ERROR_CODE_58, err_loc); /* Cannot be both .entry and .extern */
        *error_flag = TRUE;
    } else {
        sym->is_entry = TRUE;
    }
}

/*
 * Calculates the jump distance for I-Type branch instructions.
 * It finds the target label, computes the distance from the current IC,
 * and encodes the 16-bit result into the instruction image.
 * Throws an error if the label is missing or external.
 */
static void complete_i_type_branch(char operands[][MAX_LINE_LENGTH], SymbolNode *head, unsigned char instruction_image[], int IC, location err_loc, int *error_flag) {
    SymbolNode *sym = find_symbol(head, operands[BRANCH_LABEL_OP_INDEX]);
    long distance;

    if (sym == NULL) {
        print_external_error(ERROR_CODE_39, err_loc); /* Branch destination label not found */
        *error_flag = TRUE;
    } else if (sym->is_extern == TRUE) {
        print_external_error(ERROR_CODE_40, err_loc); /* Cannot branch to an external symbol */
        *error_flag = TRUE;
    } else {
        distance = sym->address - IC;

        instruction_image[IC + BYTE_OFFSET_0] |= (distance & BYTE_MASK);
        instruction_image[IC + BYTE_OFFSET_1] |= ((distance >> BITS_PER_BYTE) & BYTE_MASK);
    }
}

/*
 * Encodes the absolute 25-bit memory address of a label into a J-Type instruction.
 * If the target label is external, it leaves the address as 0 and logs the
 * instruction's IC into the externals tracking list for the .ext file.
 */
static void complete_j_type_instruction(char operands[][MAX_LINE_LENGTH], SymbolNode *head, ExternUsageNode **ext_head, unsigned char instruction_image[], int IC, location err_loc, int *error_flag) {
    SymbolNode *sym;
    long address;

    if (is_valid_label(operands[JUMP_LABEL_OP_INDEX]) == TRUE) {
        sym = find_symbol(head, operands[JUMP_LABEL_OP_INDEX]);

        if (sym == NULL) {
            print_external_error(ERROR_CODE_39, err_loc); /* Jump destination label not found */
            *error_flag = TRUE;
        } else if (sym->is_extern == TRUE) {
            add_extern_usage(ext_head, operands[JUMP_LABEL_OP_INDEX], IC);
        } else {
            address = sym->address;

            instruction_image[IC + BYTE_OFFSET_0] |= (address & BYTE_MASK);
            instruction_image[IC + BYTE_OFFSET_1] |= ((address >> BITS_PER_BYTE) & BYTE_MASK);
            instruction_image[IC + BYTE_OFFSET_2] |= ((address >> (BYTE_OFFSET_2 * BITS_PER_BYTE)) & BYTE_MASK);
            instruction_image[IC + BYTE_OFFSET_3] |= ((address >> (BYTE_OFFSET_3 * BITS_PER_BYTE)) & J_ADDRESS_BIT_24_MASK);
        }
    }
}