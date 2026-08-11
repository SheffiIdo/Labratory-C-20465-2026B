#include "../Header files/first_pass.h"
#include "../Header files/parser.h"
#include "../Header files/utils.h"
#include "../Header files/errors.h"
#include "../Header files/globals.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Private helper function declarations */
static int handle_directive_line(char *token, char *line_ptr, int has_label, char *label_name, int *DC, SymbolNode **head, location err_loc);
static int handle_instruction_line(char *token, char *line_ptr, int has_label, char *label_name, int *IC, SymbolNode **head, location err_loc);
static int process_string_directive(char *line_ptr, int *DC, location err_loc);
static int process_data_directive(char *line_ptr, int *DC, int bytes_per_item, location err_loc);
static int process_extern_directive(char *line_ptr, SymbolNode **head, location err_loc);
static int parse_r_type_instruction(char *line_ptr, InstructionDef *inst, int *IC, location err_loc);
static int parse_i_type_instruction(char *line_ptr, InstructionDef *inst, int *IC, location err_loc);

/* The arrays to store the binary image */
unsigned char instruction_image[MAX_MEMORY];
unsigned char data_image[MAX_MEMORY];

int execute_first_pass(const char *filename, SymbolNode **head) {
    FILE *file;
    char line[LINE_BUFFER_SIZE];
    int line_num = 0;
    int error_flag = FALSE;
    int ch; /* Used for clearing the buffer if a line is too long */

    int IC = IC_INIT_VALUE;
    int DC = DC_INIT_VALUE;

    location err_loc;
    err_loc.file_name = (char *)filename;

    file = fopen(filename, "r");
    if (file == NULL) {
        print_internal_error(ERROR_CODE_2); /* Cannot open file */
        return FALSE;
    }

    /* Read the file line by line */
    while (fgets(line, sizeof(line), file) != NULL) {
        char *ptr = line;
        char first_token[MAX_LINE_LENGTH] = {0};
        int has_label = FALSE;
        char label_name[MAX_LABEL_LENGTH + 2] = {0}; /* +1 for potential ':', +1 for '\0' */

        line_num++;
        err_loc.line_num = line_num;

        /* Check if the line exceeded the maximum allowed length */
        if (strchr(line, '\n') == NULL && !feof(file)) {
            print_external_error(ERROR_CODE_4, err_loc);
            error_flag = TRUE;

            /* Flush the remainder of the oversized line from the input stream */
            while ((ch = fgetc(file)) != '\n' && ch != EOF) {
                /* Do nothing */
            }
            continue; /* Skip to the next line */
        }

        /* Skip leading whitespace */
        skip_whitespace(&ptr);

        /* Ignore empty lines and comments */
        if (*ptr == '\0' || *ptr == '\n' || *ptr == COMMENT_CHAR) {
            continue;
        }

        /* Extract the first word to see what we are dealing with */
        ptr = get_next_token(ptr, first_token);

        /* Check if first_token is a label (ends with ':') */
        if (strlen(first_token) > 0 && first_token[strlen(first_token) - 1] == ':') {
            has_label = TRUE;

            /* Copy the token without the trailing colon */
            strncpy(label_name, first_token, strlen(first_token) - 1);
            label_name[strlen(first_token) - 1] = '\0';

            /* Validate the label name format */
            if (is_valid_label(label_name) == FALSE) {
                print_external_error(ERROR_CODE_52, err_loc);
                error_flag = TRUE;
                /* We continue processing to catch other errors on the line */
            }

            /* Check if the label is a reserved word */
            if (is_reserved_word(label_name) == TRUE) {
                print_external_error(ERROR_CODE_52, err_loc);
                error_flag = TRUE;
            }

            /* Since the first token was a label, grab the next token to find the operation */
            ptr = get_next_token(ptr, first_token);

            /* If the line was just a label with nothing else after it, skip */
            if (strlen(first_token) == 0) {
                continue;
            }
        }

        /*
         * If the token starts with a '.', it's a directive. Otherwise, it's an instruction.
        */
        if (first_token[0] == '.') {
            if (handle_directive_line(first_token, ptr, has_label, label_name, &DC, head, err_loc) == FALSE) {
                error_flag = TRUE;
            }
        } else {
            if (handle_instruction_line(first_token, ptr, has_label, label_name, &IC, head, err_loc) == FALSE) {
                error_flag = TRUE;
            }
        }

         /* Check for memory overflow */
         if (IC + DC >= MAX_MEMORY) {
             print_external_error(ERROR_CODE_56, err_loc);
             error_flag = TRUE;
             break;
         }
    }

    fclose(file);

    /* Update data symbol addresses by adding final IC */
    if (error_flag == FALSE) {
        update_data_symbols_address(*head, IC);
    }

    return (error_flag == FALSE);
}

static int handle_directive_line(char *token, char *line_ptr, int has_label, char *label_name, int *DC, SymbolNode **head, location err_loc) {
    int error_flag = FALSE;

    /* Data Storage Directives */
    if (strcmp(token, ".db") == STRING_MATCH || strcmp(token, ".dh") == STRING_MATCH ||
        strcmp(token, ".dw") == STRING_MATCH || strcmp(token, ".asciz") == STRING_MATCH) {

        /* If a label exists, securely add it to the Symbol Table */
        if (has_label == TRUE) {
            if (find_symbol(*head, label_name) != NULL) {
                print_external_error(ERROR_CODE_51, err_loc); /* Label defined more than once */
                error_flag = TRUE;
            } else {
                add_symbol(head, label_name, *DC, DATA_SYMBOL);
            }
        }

        /* Delegate to the specific processor to extract values and advance DC */
        if (strcmp(token, ".asciz") == STRING_MATCH) {
            if (process_string_directive(line_ptr, DC, err_loc) == FALSE) error_flag = TRUE;
        } else if (strcmp(token, ".db") == STRING_MATCH) {
            if (process_data_directive(line_ptr, DC, 1, err_loc) == FALSE) error_flag = TRUE;
        } else if (strcmp(token, ".dh") == STRING_MATCH) {
            if (process_data_directive(line_ptr, DC, 2, err_loc) == FALSE) error_flag = TRUE;
        } else if (strcmp(token, ".dw") == STRING_MATCH) {
            if (process_data_directive(line_ptr, DC, 4, err_loc) == FALSE) error_flag = TRUE;
        }
    }
    /* Extern Directive */
    else if (strcmp(token, ".extern") == STRING_MATCH) {
        /* Label before .extern is meaningless and ignored */
        if (process_extern_directive(line_ptr, head, err_loc) == FALSE) {
            error_flag = TRUE;
        }
    }
    /* Entry Directive */
    else if (strcmp(token, ".entry") == STRING_MATCH) {
        /* .entry is handled entirely in the Second Pass, so we just skip it here */
    }
    else {
        /* Not a recognized directive */
        print_external_error(ERROR_CODE_30, err_loc);
        error_flag = TRUE;
    }

    return (error_flag == FALSE);
}

static int handle_instruction_line(char *token, char *line_ptr, int has_label, char *label_name, int *IC, SymbolNode **head, location err_loc) {
    InstructionDef inst;
    int error_flag = FALSE;

    /* If a label exists, securely add it to the Symbol Table */
    if (has_label == TRUE) {
        if (find_symbol(*head, label_name) != NULL) {
            print_external_error(ERROR_CODE_51, err_loc); /* Label defined more than once */
            error_flag = TRUE;
        } else {
            add_symbol(head, label_name, *IC, CODE_SYMBOL);
        }
    }

    /* Look up the instruction in our dictionary */
    if (get_instruction(token, &inst) == FALSE) {
        print_external_error(ERROR_CODE_30, err_loc); /* Illegal opcode */
        return FALSE;
    }

    /* Parse operands and build the partial machine code */
    if (inst.type == R_TYPE) {
        if (parse_r_type_instruction(line_ptr, &inst, IC, err_loc) == FALSE) {
            error_flag = TRUE;
        }
    } else if (inst.type == I_TYPE) {
        if (parse_i_type_instruction(line_ptr, &inst, IC, err_loc) == FALSE) {
            error_flag = TRUE;
        }
    } else if (inst.type == J_TYPE) {
        /* TO DO: parse_j_type_instruction() */
    } else {
        return FALSE; /* Unknown type safeguard */
    }

    /* Every instruction takes exactly 4 bytes (32 bits) in memory */
    (*IC) += BYTES_PER_INSTRUCTION;

    return (error_flag == FALSE);
}

static int process_string_directive(char *line_ptr, int *DC, location err_loc) {
    int error_flag = FALSE;

    skip_whitespace(&line_ptr);

    /* Check for opening quote */
    if (*line_ptr != '"') {
        print_external_error(ERROR_CODE_54, err_loc); /* Missing opening/closing quotes */
        return FALSE;
    }

    line_ptr++; /* Skip the opening quote */

    /* Read characters until the closing quote or end of line */
    while (*line_ptr != '"' && *line_ptr != '\0' && *line_ptr != '\n') {
        data_image[*DC] = *line_ptr;
        (*DC)++;
        line_ptr++;
    }

    /* Check if we actually found the closing quote */
    if (*line_ptr != '"') {
        print_external_error(ERROR_CODE_54, err_loc); /* Missing closing quote */
        return FALSE;
    }

    line_ptr++; /* Skip the closing quote */

    /* Add the required null terminator */
    data_image[*DC] = '\0';
    (*DC)++;

    /* Check for garbage text after the closing quote */
    skip_whitespace(&line_ptr);
    if (*line_ptr != '\0' && *line_ptr != '\n' && *line_ptr != COMMENT_CHAR) {
        print_external_error(ERROR_CODE_32, err_loc); /* Extraneous text */
        error_flag = TRUE;
    }

    return (error_flag == FALSE);
}

static int process_data_directive(char *line_ptr, int *DC, int bytes_per_item, location err_loc) {
    long value;
    char *end_ptr;
    int i;

    skip_whitespace(&line_ptr);

    /* Missing arguments */
    if (*line_ptr == '\0' || *line_ptr == '\n' || *line_ptr == COMMENT_CHAR) {
        print_external_error(ERROR_CODE_31, err_loc);
        return FALSE;
    }

    /* Illegal comma before the first number */
    if (*line_ptr == ',') {
        print_external_error(ERROR_CODE_36, err_loc);
        return FALSE;
    }

    /* Loop through the comma-separated list */
    while (*line_ptr != '\0' && *line_ptr != '\n' && *line_ptr != COMMENT_CHAR) {

        /* Parse the integer. strtol automatically handles negative signs and whitespace */
        value = strtol(line_ptr, &end_ptr, DECIMAL_BASE);

        /* If the pointer didn't move, it didn't find a valid number */
        if (line_ptr == end_ptr) {
            if (*line_ptr == ',') {
                print_external_error(ERROR_CODE_35, err_loc); /* Consecutive commas */
            } else {
                print_external_error(ERROR_CODE_53, err_loc); /* Non-numeric values */
            }
            return FALSE;
        }

        /* Shift our reading pointer to immediately after the number */
        line_ptr = end_ptr;

        /* Store the value in data_image in strictly little-endian format */
        for (i = 0; i < bytes_per_item; i++) {
            /* Slice out the exact 8-bit byte we need using a bit mask */
            data_image[*DC] = (value >> (i * BITS_PER_BYTE)) & BYTE_MASK;
            (*DC)++;
        }

        skip_whitespace(&line_ptr);

        /* If we reached the end of the line safely, we are done */
        if (*line_ptr == '\0' || *line_ptr == '\n' || *line_ptr == COMMENT_CHAR) {
            break;
        }

        /* If the next character isn't a comma, the user forgot one */
        if (*line_ptr != ',') {
            print_external_error(ERROR_CODE_34, err_loc); /* Missing comma between operands */
            return FALSE;
        }

        /* It is a comma. Skip past it and clear any spaces after it */
        line_ptr++;
        skip_whitespace(&line_ptr);

        /* Rule: Illegal trailing comma at the end of the line[cite: 1] */
        if (*line_ptr == '\0' || *line_ptr == '\n' || *line_ptr == COMMENT_CHAR) {
            print_external_error(ERROR_CODE_32, err_loc); /* Extraneous text (trailing comma) */
            return FALSE;
        }
    }

    return TRUE;
}

static int process_extern_directive(char *line_ptr, SymbolNode **head, location err_loc) {
    char label_name[MAX_LINE_LENGTH] = {0};
    int error_flag = FALSE;

    /* Get the operand (the external label name) */
    line_ptr = get_next_token(line_ptr, label_name);

    if (strlen(label_name) == 0) {
        print_external_error(ERROR_CODE_31, err_loc); /* Missing arguments */
        return FALSE;
    }

    if (is_valid_label(label_name) == FALSE) {
        print_external_error(ERROR_CODE_52, err_loc); /* Illegal label name */
        error_flag = TRUE;
    }

    /* Check for garbage after the label */
    skip_whitespace(&line_ptr);
    if (*line_ptr != '\0' && *line_ptr != '\n' && *line_ptr != COMMENT_CHAR) {
        print_external_error(ERROR_CODE_32, err_loc); /* Extraneous text */
        error_flag = TRUE;
    }

    /* Add to symbol table with value 0 if no errors */
    if (error_flag == FALSE) {
        add_symbol(head, label_name, 0, EXTERN_SYMBOL);
    }

    return (error_flag == FALSE);
}

static int parse_r_type_instruction(char *line_ptr, InstructionDef *inst, int *IC, location err_loc) {
    char operands[MAX_OPERANDS][MAX_LINE_LENGTH] = {{0}};
    int operand_count = 0;
    int expected_operands = (inst->opcode == 0) ? R_ARITHMETIC_OP_COUNT : R_COPY_OP_COUNT;
    int rs = 0, rt = 0, rd = 0;
    int reg_num, i;
    long machine_code;

    /* Delegate all comma and formatting checks to our new tool! */
    if (extract_operands(line_ptr, operands, &operand_count, err_loc) == FALSE) {
        return FALSE; /* Error was already printed by extract_operands */
    }

    /* Check operand counts */
    if (operand_count < expected_operands) {
        print_external_error(ERROR_CODE_31, err_loc); /* Missing arguments */
        return FALSE;
    }
    if (operand_count > expected_operands) {
        print_external_error(ERROR_CODE_32, err_loc); /* Extraneous text */
        return FALSE;
    }

    /* Validate and assign registers safely */
    for (i = 0; i < expected_operands; i++) {
        if (parse_register(operands[i], &reg_num) == FALSE) {
            print_external_error(ERROR_CODE_33, err_loc); /* Illegal register name */
            return FALSE;
        }

        /* Route to the correct struct position based on instruction architecture */
        if (expected_operands == R_ARITHMETIC_OP_COUNT) {
            if (i == 0) rs = reg_num;
            else if (i == 1) rt = reg_num;
            else rd = reg_num;
        } else {
            /* 2 operands (move, mvhi, mvlo): rs and rd */
            if (i == 0) rs = reg_num;
            else rd = reg_num;
        }
    }

    /* Build the 32-bit machine code */
    machine_code = 0;
    machine_code |= ((long)inst->opcode << OPCODE_SHIFT);
    machine_code |= ((long)rs << RS_SHIFT);
    machine_code |= ((long)rt << RT_SHIFT);
    machine_code |= ((long)rd << RD_SHIFT);
    machine_code |= ((long)inst->funct << FUNCT_SHIFT);

    /* Store into little-endian memory */
    for (i = 0; i < BYTES_PER_INSTRUCTION; i++) {
        instruction_image[*IC + i] = (machine_code >> (i * BITS_PER_BYTE)) & BYTE_MASK;
    }

    return TRUE;
}

static int parse_i_type_instruction(char *line_ptr, InstructionDef *inst, int *IC, location err_loc) {
    char operands[MAX_OPERANDS][MAX_LINE_LENGTH] = {{0}};
    int operand_count = 0;
    int rs = 0, rt = 0;
    long immed = 0;
    long machine_code;
    int i;

    /* Extract all comma-separated operands */
    if (extract_operands(line_ptr, operands, &operand_count, err_loc) == FALSE) {
        return FALSE;
    }

    /* Check exact operand counts */
    if (operand_count < I_TYPE_OP_COUNT) {
        print_external_error(ERROR_CODE_31, err_loc); /* Missing arguments */
        return FALSE;
    }
    if (operand_count > I_TYPE_OP_COUNT) {
        print_external_error(ERROR_CODE_32, err_loc); /* Extraneous text */
        return FALSE;
    }

    /* Differentiate between Branch instructions and Arithmetic/Memory instructions */
    /* Branch Opcodes: 15 (bne), 16 (beq), 17 (blt), 18 (bgt) */
    if (inst->opcode >= MIN_BRANCH_OPCODE && inst->opcode <= MAX_BRANCH_OPCODE) {
        /* Format: rs, rt, label */
        if (parse_register(operands[0], &rs) == FALSE || parse_register(operands[1], &rt) == FALSE) {
            print_external_error(ERROR_CODE_33, err_loc); /* Invalid register */
            return FALSE;
        }
        if (is_valid_label(operands[2]) == FALSE) {
            print_external_error(ERROR_CODE_52, err_loc); /* Invalid label format */
            return FALSE;
        }
        /* The distance to the label is calculated in the Second Pass, so we leave immed as 0 */
        immed = 0;
    } else {
        /* Format: rs, immed, rt */
        if (parse_register(operands[0], &rs) == FALSE || parse_register(operands[2], &rt) == FALSE) {
            print_external_error(ERROR_CODE_33, err_loc); /* Invalid register */
            return FALSE;
        }
        if (parse_immediate(operands[1], &immed) == FALSE) {
            print_external_error(ERROR_CODE_38, err_loc); /* Invalid immediate number */
            return FALSE;
        }
    }

    /* Build the 32-bit machine code */
    machine_code = 0;
    machine_code |= ((long)inst->opcode << OPCODE_SHIFT);
    machine_code |= ((long)rs << RS_SHIFT);
    machine_code |= ((long)rt << RT_SHIFT);
    machine_code |= (immed & IMMED_MASK); /* Mask prevents negative sign extension from bleeding over */

    /* Store into little-endian memory */
    for (i = 0; i < BYTES_PER_INSTRUCTION; i++) {
        instruction_image[*IC + i] = (machine_code >> (i * BITS_PER_BYTE)) & BYTE_MASK;
    }

    return TRUE;
}