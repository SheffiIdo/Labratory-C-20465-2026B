#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Header files/errors.h"

/* The Following array specifies the error code numbers and the corresponding error message. */

Error errors[] = {
        /* 0 - 14: System and Macro Errors */
        {ERROR_CODE_0,  "No Error"},
        {ERROR_CODE_1,  "Failed to dynamically allocate memory"},
        {ERROR_CODE_2,  "Cannot open file for reading"},
        {ERROR_CODE_3,  "Cannot open file for writing"},
        {ERROR_CODE_4,  "Source line exceeds the maximum length of 80 characters"},
        {ERROR_CODE_5,  "Macro declared without a name definition"},
        {ERROR_CODE_6,  "Extra text found after macro name definition"},
        {ERROR_CODE_7,  "Extra text found after 'mcroend'"},
        {ERROR_CODE_8,  "Macro name cannot be a reserved instruction or directive keyword"},
        {ERROR_CODE_9,  "Macro has more than one definition"},
        {ERROR_CODE_10, "Illegal character in macro name"},
        {ERROR_CODE_11, "Nested macro definition is illegal"},
        {ERROR_CODE_12, "Missing 'mcroend' before end of file"},
        {ERROR_CODE_13, "Macro name exceeds maximum allowed length (31 characters)"},
        {ERROR_CODE_14, "Illegal characters in macro name. Must start with a letter and contain only letters, numbers, or '_'."},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},

        /* 30 - 39: Instruction Parsing Errors */
        {ERROR_CODE_30, "Illegal opcode (instruction not recognized)"},
        {ERROR_CODE_31, "Missing arguments for instruction"},
        {ERROR_CODE_32, "Extra extraneous text found at the end of the line"},
        {ERROR_CODE_33, "Illegal register name (must be between $0 and $31)"},
        {ERROR_CODE_34, "Missing comma between operands"},
        {ERROR_CODE_35, "Illegal consecutive commas"},
        {ERROR_CODE_36, "Illegal comma placed before the first operand"},
        {ERROR_CODE_37, "Operand is out of bounds for 16-bit 2's complement representation"},
        {ERROR_CODE_38, "Unrecognized operand type for this specific instruction"},
        {ERROR_CODE_39, "Cannot branch or jump to a label that does not exist"},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},

        /* 50 - 56: Data Directive & Label Errors */
        {ERROR_CODE_50, "Label declaration must end with ':'"},
        {ERROR_CODE_51, "Label is defined more than once in the source file"},
        {ERROR_CODE_52, "Illegal label name (must start with letter, alphanumeric, max 31 chars)"},
        {ERROR_CODE_53, "Data directive (.db, .dh, .dw) contains non-numeric values"},
        {ERROR_CODE_54, "Missing opening or closing quotes in .asciz directive"},
        {ERROR_CODE_55, "Label is declared as .extern but is defined locally in the file"},
        {ERROR_CODE_56, "Memory overflow: Instruction and Data counters exceed maximum memory"},
};

void print_internal_error(int error_code) {
    /* Print the error code number and the error message */
    printf("~~ERROR: ID:%d~~ | %s\n", error_code, errors[error_code].error_msg);

    /* If the error is fatal, terminate */
    if (error_code == ERROR_CODE_1) {
        exit(EXIT_FAILURE);
    }
}

void print_external_error(int error_code, location file) {
    /* Print the error code number, file name, assembly line number and the error message */
    printf("~~ERROR: ID:%d~~ in %s at line:%d | there is error: %s\n",
           error_code, file.file_name, file.line_num, errors[error_code].error_msg);
}