#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Represents the exact location of an error in the source code */
typedef struct {
    char *file_name;
    int line_num;
} location;

/* Represents an error with an associated error ID and error message */
typedef struct Error {
    int error_id;     /* Unique identifier for the error */
    char *error_msg;  /* Error message associated with the error */
} Error;

/* Represents error codes for various types of errors */
typedef enum ERROR_CODES {
    /*
     * SYSTEM & MACRO ERRORS
     */
    ERROR_CODE_0 = 0,
    ERROR_CODE_1,
    ERROR_CODE_2,
    ERROR_CODE_3,
    ERROR_CODE_4,
    ERROR_CODE_5,
    ERROR_CODE_6,
    ERROR_CODE_7,
    ERROR_CODE_8,
    ERROR_CODE_9,
    ERROR_CODE_10,
    ERROR_CODE_11,
    ERROR_CODE_12,

    /*
     * INSTRUCTION PARSING ERRORS
     */
    ERROR_CODE_30 = 30,
    ERROR_CODE_31,
    ERROR_CODE_32,
    ERROR_CODE_33,
    ERROR_CODE_34,
    ERROR_CODE_35,
    ERROR_CODE_36,
    ERROR_CODE_37,
    ERROR_CODE_38,
    ERROR_CODE_39,

    /*
     * DATA DIRECTIVE & LABEL ERRORS
     */
    ERROR_CODE_50 = 50,
    ERROR_CODE_51,
    ERROR_CODE_52,
    ERROR_CODE_53,
    ERROR_CODE_54,
    ERROR_CODE_55
} ERROR_CODES;


/**
 * This function prints to stdout an error that is related to a specific line in the source file.
 * @param error_code an integer representing the unique error number
 * @param file a location struct containing the source file name and line information
 */
void print_external_error(int error_code, location file);

/**
 * This function prints to stdout an error that is a result of an internal process and not an error in the source file.
 * @param error_code an integer representing the unique error number
 */
void print_internal_error(int error_code);

#endif