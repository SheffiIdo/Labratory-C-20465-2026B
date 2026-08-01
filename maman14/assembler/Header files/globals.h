#ifndef GLOBALS_H
#define GLOBALS_H

/*
 * BOOLEAN DEFINITIONS
 */
#define TRUE 1
#define FALSE 0

/*
 * STRING & MEMORY CONSTANTS
 */
#define STRING_MATCH 0           /* Return value of strcmp when strings match */
#define NULL_CHAR_LEN 1          /* Extra byte required for '\0' */
#define TERMINATOR_PADDING 2     /* Extra bytes for '\n' and '\0' in line buffers */

/*
 * ASSEMBLER SYSTEM CONSTRAINTS
 */
#define MAX_LINE_LENGTH 80       /* Max chars per line */
#define LINE_BUFFER_SIZE (MAX_LINE_LENGTH + TERMINATOR_PADDING)

#define MAX_LABEL_LENGTH 31      /* Max chars for a valid label/symbol name */

#define IC_INIT_VALUE 100        /* Instruction Counter starting address */
#define DC_INIT_VALUE 0          /* Data Counter starting address */

/*
 * FILE EXTENSIONS
 */
#define AS_EXTENSION ".as"       /* Raw assembly source */
#define AM_EXTENSION ".am"       /* Macro-expanded intermediate file */
#define OB_EXTENSION ".ob"       /* Object binary code file */
#define ENT_EXTENSION ".ent"     /* Entries output file */
#define EXT_EXTENSION ".ext"     /* Externals output file */

/*
 * SYNTAX TOKENS & RULES
 */
#define MACRO_START_TOKEN "mcro"
#define MACRO_END_TOKEN "mcroend"
#define COMMENT_CHAR ';'
#define MACRO_DEF_TOKENS 2
#define MACRO_END_TOKENS 1

#endif