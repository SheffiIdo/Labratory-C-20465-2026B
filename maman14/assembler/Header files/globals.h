#ifndef GLOBALS_H
#define GLOBALS_H

/*
 * boolean definitions
 */
#define TRUE 1
#define FALSE 0

/*
 * string and memory constants
 */
#define STRING_MATCH 0           /* Return value of strcmp when strings match */
#define NULL_CHAR_LEN 1          /* Extra byte required for '\0' */
#define TERMINATOR_PADDING 2     /* Extra bytes for '\n' and '\0' in line buffers */

/*
 * binary, memory, and conversion constants
 */
#define BITS_PER_BYTE 8
#define BYTE_MASK 0xFF
#define IMMED_MASK 0xFFFF
#define BYTES_PER_INSTRUCTION 4
#define DECIMAL_BASE 10
#define MAX_MEMORY 4096          /* Maximum memory size of the imaginary machine */
#define BYTE_OFFSET_0 0          /* Machine code byte placement */
#define BYTE_OFFSET_1 1
#define BYTE_OFFSET_2 2
#define BYTE_OFFSET_3 3

/*
 * Instruction binary shift constants
 */
#define OPCODE_SHIFT 26
#define RS_SHIFT 21
#define RT_SHIFT 16
#define RD_SHIFT 11
#define FUNCT_SHIFT 6

/*
 * parsing boundaries
 */
#define MAX_OPERANDS 40
#define BRANCH_LABEL_OP_INDEX 2
#define JUMP_LABEL_OP_INDEX 0

/*
 * assembler system constraints
 */
#define MAX_LINE_LENGTH 80       /* Max chars per line */
#define LINE_BUFFER_SIZE (MAX_LINE_LENGTH + TERMINATOR_PADDING)
#define MAX_LABEL_LENGTH 31      /* Max chars for a valid label/symbol name */
#define IC_INIT_VALUE 100        /* Instruction Counter starting address */
#define DC_INIT_VALUE 0          /* Data Counter starting address */
#define MINIMUM_ARGS 2

/*
 * Expected operand counts for instructions
 */
#define R_ARITHMETIC_OP_COUNT 3  /* e.g., add, sub, and, or, nor */
#define R_COPY_OP_COUNT 2        /* e.g., move, mvhi, mvlo */
#define I_TYPE_OP_COUNT 3

/*
 * J-Type Instruction constraints
 */
#define J_TYPE_OP_COUNT 1
#define J_TYPE_STOP_OP_COUNT 0
#define REG_BIT_SHIFT 25
#define JMP_OPCODE 30
#define STOP_OPCODE 63
#define J_ADDRESS_BIT_24_MASK 0x01 /* Mask to isolate the 25th bit for J-Type addresses */

/*
 * Instruction opcode boundaries
 */
#define MIN_BRANCH_OPCODE 15
#define MAX_BRANCH_OPCODE 18

/*
 * register and immediate boundaries
 */
#define MIN_REGISTER 0
#define MAX_REGISTER 31
#define MIN_IMMED -32768
#define MAX_IMMED 32767

/*
 * file extensions
 */
#define AS_EXTENSION ".as"       /* Raw assembly source */
#define AM_EXTENSION ".am"       /* Macro-expanded intermediate file */
#define OB_EXTENSION ".ob"       /* Object binary code file */
#define ENT_EXTENSION ".ent"     /* Entries output file */
#define EXT_EXTENSION ".ext"     /* Externals output file */

/*
 * syntax tokens and rules
 */
#define MACRO_START_TOKEN "mcro"
#define MACRO_END_TOKEN "mcroend"
#define COMMENT_CHAR ';'
#define MACRO_DEF_TOKENS 2
#define MACRO_END_TOKENS 1

/* Symbol attributes to distinguish label types in the Symbol Table */
typedef enum {
 CODE_SYMBOL,   /* For labels pointing to instructions */
 DATA_SYMBOL,   /* For labels pointing to .db, .dh, .dw, .asciz */
 EXTERN_SYMBOL, /* For .extern labels */
 ENTRY_SYMBOL   /* For .entry labels */
} SymbolAttribute;

/* Enum for classifying the type of line being parsed */
typedef enum {
 INSTRUCTION_LINE,   /* e.g., add, sub, jmp */
 DIRECTIVE_LINE,     /* e.g., .db, .asciz, .extern */
 EMPTY_OR_COMMENT,   /* Blank lines or lines starting with ; */
 ERROR_LINE          /* A line with a syntax error */
} LineType;

/* Enum for instruction architecture types */
typedef enum {
 R_TYPE,
 I_TYPE,
 J_TYPE,
 UNKNOWN_TYPE
} InstructionType;

/* Struct defining a machine instruction's properties */
typedef struct {
 InstructionType type;   /* R_TYPE, I_TYPE, or J_TYPE */
 int opcode;             /* 0-63 */
 int funct;              /* Used for R-Type, 0 for others */
} InstructionDef;

/* Global variables (up to 9)*/
extern int memory_allocation_fail;

#endif