#include "../Header files/parser.h"
#include "../Header files/utils.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int get_instruction(const char *name, InstructionDef *inst) {
    if (name == NULL || inst == NULL) {
        return FALSE;
    }

    /* R-Type Instructions */
    if (strcmp(name, "add") == STRING_MATCH) {
        inst->type = R_TYPE; inst->opcode = 0; inst->funct = 1; return TRUE;
    } else if (strcmp(name, "sub") == STRING_MATCH) {
        inst->type = R_TYPE; inst->opcode = 0; inst->funct = 2; return TRUE;
    } else if (strcmp(name, "and") == STRING_MATCH) {
        inst->type = R_TYPE; inst->opcode = 0; inst->funct = 3; return TRUE;
    } else if (strcmp(name, "or") == STRING_MATCH) {
        inst->type = R_TYPE; inst->opcode = 0; inst->funct = 4; return TRUE;
    } else if (strcmp(name, "nor") == STRING_MATCH) {
        inst->type = R_TYPE; inst->opcode = 0; inst->funct = 5; return TRUE;
    } else if (strcmp(name, "move") == STRING_MATCH) {
        inst->type = R_TYPE; inst->opcode = 1; inst->funct = 1; return TRUE;
    } else if (strcmp(name, "mvhi") == STRING_MATCH) {
        inst->type = R_TYPE; inst->opcode = 1; inst->funct = 2; return TRUE;
    } else if (strcmp(name, "mvlo") == STRING_MATCH) {
        inst->type = R_TYPE; inst->opcode = 1; inst->funct = 3; return TRUE;
    }

    /* I-Type Instructions */
    else if (strcmp(name, "addi") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 10; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "subi") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 11; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "andi") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 12; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "ori") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 13; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "nori") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 14; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "bne") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 15; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "beq") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 16; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "blt") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 17; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "bgt") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 18; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "lb") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 19; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "sb") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 20; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "lw") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 21; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "sw") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 22; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "lh") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 23; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "sh") == STRING_MATCH) {
        inst->type = I_TYPE; inst->opcode = 24; inst->funct = 0; return TRUE;
    }

    /* J-Type Instructions */
    else if (strcmp(name, "jmp") == STRING_MATCH) {
        inst->type = J_TYPE; inst->opcode = 30; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "la") == STRING_MATCH) {
        inst->type = J_TYPE; inst->opcode = 31; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "call") == STRING_MATCH) {
        inst->type = J_TYPE; inst->opcode = 32; inst->funct = 0; return TRUE;
    } else if (strcmp(name, "hlt") == STRING_MATCH) {
        inst->type = J_TYPE; inst->opcode = 63; inst->funct = 0; return TRUE;
    }

    return FALSE;
}

int is_valid_label(const char *word) {
    int i;
    int len;

    if (word == NULL) {
        return FALSE;
    }

    len = strlen(word);

    if (len == 0 || len > MAX_LABEL_LENGTH) {
        return FALSE;
    }

    /* First character must be an letter */
    if (!isalpha((unsigned char)word[0])) {
        return FALSE;
    }

    /* Remaining characters must be only letters or numbers */
    for (i = 1; i < len; i++) {
        if (!isalnum((unsigned char)word[i])) {
            return FALSE;
        }
    }

    return TRUE;
}

char *get_next_token(char *line, char *word) {
    int i = 0;

    skip_whitespace(&line);

    /* Read characters until a delimiter or end of string is encountered */
    while (*line != '\0' && *line != ' ' && *line != '\t' && *line != ',' && *line != '\n') {
        word[i] = *line;
        i++;
        line++;
    }

    /* Terminate the extracted string securely */
    word[i] = '\0';

    return line;
}

int parse_register(const char *operand, int *reg_num) {
    char *end_ptr;
    long val;

    /* A register must start with '$' and contain at least one more character */
    if (operand == NULL || operand[0] != '$' || operand[1] == '\0') {
        return FALSE;
    }

    /* This blocks '+', '-', spaces, or letters (e.g., $+1, $-5, $ A) */
    if (!isdigit(operand[1])) {
        return FALSE;
    }

    /* If the first digit is '0' and there is another character after it, it's illegal */
    if (operand[1] == '0' && operand[2] != '\0') {
        return FALSE;
    }

    /* Convert the rest of the string (after the '$') to a long integer */
    val = strtol(&operand[1], &end_ptr, DECIMAL_BASE);

    /*
     * If end_ptr doesn't point to the null terminator, there was garbage after the number (e.g., "$3a").
     * Also, enforce the 0 to 31 boundary limit.
     */
    if (*end_ptr != '\0' || val < MIN_REGISTER || val > MAX_REGISTER) {
        return FALSE;
    }

    *reg_num = (int)val;
    return TRUE;
}

int parse_immediate(const char *operand, long *immed) {
    char *end_ptr;
    long val;

    if (operand == NULL || operand[0] == '\0') {
        return FALSE;
    }

    /* Convert the string to a long integer. Automatically handles '-' and '+' */
    val = strtol(operand, &end_ptr, DECIMAL_BASE);

    /*
     * If end_ptr doesn't point to the null terminator, it wasn't a pure number.
     * Also, enforce the 16-bit 2's complement boundary limit.
     */
    if (*end_ptr != '\0' || val < MIN_IMMED || val > MAX_IMMED) {
        return FALSE;
    }

    *immed = val;
    return TRUE;
}

int extract_operands(char *line_ptr, char operands[][MAX_LINE_LENGTH], int *operand_count, location err_loc) {
    *operand_count = 0;
    skip_whitespace(&line_ptr);

    /* Empty operands are technically valid (e.g., a line with just "hlt") */
    if (*line_ptr == '\0' || *line_ptr == '\n') {
        return TRUE;
    }

    /* Illegal comma before the first operand */
    if (*line_ptr == ',') {
        print_external_error(ERROR_CODE_36, err_loc);
        return FALSE;
    }

    while (*line_ptr != '\0' && *line_ptr != '\n') {

        /* Protection against buffer overflow */
        if (*operand_count >= MAX_OPERANDS) {
            print_external_error(ERROR_CODE_32, err_loc); /* Extraneous text */
            return FALSE;
        }

        /* Extract the text into our cleanly separated array */
        line_ptr = get_next_token(line_ptr, operands[*operand_count]);
        (*operand_count)++;

        skip_whitespace(&line_ptr);

        /* If we hit the end of the line safely, break out */
        if (*line_ptr == '\0' || *line_ptr == '\n') {
            break;
        }

        /* If there is more text but the next character isn't a comma, it's an error */
        if (*line_ptr != ',') {
            print_external_error(ERROR_CODE_34, err_loc); /* Missing comma */
            return FALSE;
        }

        line_ptr++; /* Skip over the valid comma */
        skip_whitespace(&line_ptr);

        /* Illegal trailing comma */
        if (*line_ptr == '\0' || *line_ptr == '\n') {
            print_external_error(ERROR_CODE_32, err_loc); /* Extraneous text (trailing comma) */
            return FALSE;
        }

        /* Illegal consecutive commas */
        if (*line_ptr == ',') {
            print_external_error(ERROR_CODE_35, err_loc); /* Multiple consecutive commas */
            return FALSE;
        }
    }

    return TRUE;
}