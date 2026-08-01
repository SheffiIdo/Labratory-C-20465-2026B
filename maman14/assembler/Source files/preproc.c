#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Header files/preproc.h"
#include "../Header files/macro_table.h"
#include "../Header files/errors.h"

/* =========================================================================
 * HELPER: trim_leading_whitespace
 * Skips spaces and tabs at the start of a line.
 * ========================================================================= */
static void trim_leading_whitespace(char *output, const char *input) {
    while (isspace((unsigned char)*input)) {
        input++;
    }
    strcpy(output, input);
}

/* =========================================================================
 * HELPER: is_reserved_word
 * Checks if a macro name illegally uses an instruction or directive name.
 * ========================================================================= */
static int is_reserved_word(const char *name) {
    int i;
    /* Look-Up Table of all reserved language keywords */
    static const char *reserved[] = {
        "add", "sub", "and", "or", "nor", "move", "mvhi", "mvlo",
        "addi", "subi", "andi", "ori", "nori", "bne", "beq", "blt", "bgt",
        "lb", "sb", "lw", "sw", "lh", "sh", "jmp", "la", "call", "hlt",
        ".db", ".dh", ".dw", ".asciz", ".entry", ".extern", "mcro", "mcroend"
    };
    int num_reserved = sizeof(reserved) / sizeof(reserved[0]);

    for (i = 0; i < num_reserved; i++) {
        if (strcmp(name, reserved[i]) == STRING_MATCH) {
            return TRUE; /* It is a reserved word */
        }
    }
    return FALSE; /* Safe to use */
}

/* =========================================================================
 * FUNCTION: expand_macros
 * Executes the First Phase of the compilation pipeline.
 * ========================================================================= */
int expand_macros(const char *base_filename) {
    /* C90 standard: All variable declarations at the top of the block */
    char input_name[FILENAME_MAX];
    char output_name[FILENAME_MAX];
    char line[LINE_BUFFER_SIZE];
    char trimmed[LINE_BUFFER_SIZE];

    FILE *in_fp = NULL;
    FILE *out_fp = NULL;
    MacroNode *macro_table = NULL;

    int is_inside_macro = FALSE;  /* Flag: TRUE if currently reading a macro body */
    int error_found = FALSE;      /* Flag: TRUE if any syntax error is found */
    int line_counter = 0;         /* Tracks the current line number */

    char current_mcro_name[MAX_LABEL_LENGTH + NULL_CHAR_LEN] = "";
    location current_loc;         /* Struct to pass to the error engine */

    /* Construct file names using our global macros */
    sprintf(input_name, "%s%s", base_filename, AS_EXTENSION);
    sprintf(output_name, "%s%s", base_filename, AM_EXTENSION);

    current_loc.file_name = input_name;

    /* Open the raw .as file for reading */
    in_fp = fopen(input_name, "r");
    if (in_fp == NULL) {
        print_internal_error(ERROR_CODE_2);
        return FALSE;
    }

    /* Open the .am file for writing */
    out_fp = fopen(output_name, "w");
    if (out_fp == NULL) {
        print_internal_error(ERROR_CODE_3);
        fclose(in_fp);
        return FALSE;
    }

    /* Process the file line-by-line */
    while (fgets(line, sizeof(line), in_fp) != NULL) {
        line_counter++;
        current_loc.line_num = line_counter;

        /* Check if the line exceeded the 80-character limit */
        if (strchr(line, '\n') == NULL && !feof(in_fp)) {
            print_external_error(ERROR_CODE_4, current_loc);
            error_found = TRUE;
            /* Flush the remainder of the oversized line to reset the buffer */
            while (fgets(line, sizeof(line), in_fp) != NULL && strchr(line, '\n') == NULL);
            continue;
        }

        trim_leading_whitespace(trimmed, line);

        /* Ignore empty lines or comment lines entirely */
        if (trimmed[0] == '\0' || trimmed[0] == COMMENT_CHAR) {
            continue;
        }

        /* -----------------------------------------------------------------
         * SCENARIO A: Macro Declaration Start ("mcro <name>")
         * ----------------------------------------------------------------- */
        if (strncmp(trimmed, MACRO_START_TOKEN, strlen(MACRO_START_TOKEN)) == STRING_MATCH &&
            isspace((unsigned char)trimmed[strlen(MACRO_START_TOKEN)])) {

            char token1[LINE_BUFFER_SIZE];
            char token2[LINE_BUFFER_SIZE];
            char extra[LINE_BUFFER_SIZE];
            int scanned_items = sscanf(trimmed, "%s %s %s", token1, token2, extra);

            if (scanned_items < MACRO_DEF_TOKENS) {
                print_external_error(ERROR_CODE_5, current_loc); /* Missing name */
                error_found = TRUE;
            }
            else if (scanned_items > MACRO_DEF_TOKENS) {
                print_external_error(ERROR_CODE_6, current_loc); /* Extra text */
                error_found = TRUE;
            }
            else if (is_reserved_word(token2) == TRUE) {
                print_external_error(ERROR_CODE_8, current_loc); /* Reserved keyword */
                error_found = TRUE;
            }
            else if (find_macro(macro_table, token2) != NULL) {
                print_external_error(ERROR_CODE_9, current_loc); /* Macro redefined */
                error_found = TRUE;
            }
            else {
                /* Valid macro definition, start recording */
                is_inside_macro = TRUE;
                strcpy(current_mcro_name, token2);
            }
            continue;
        }

        /* -----------------------------------------------------------------
         * SCENARIO B: Macro Declaration End ("mcroend")
         * ----------------------------------------------------------------- */
        if (strncmp(trimmed, MACRO_END_TOKEN, strlen(MACRO_END_TOKEN)) == STRING_MATCH) {
            char token1[LINE_BUFFER_SIZE];
            char extra[LINE_BUFFER_SIZE];
            int scanned_items = sscanf(trimmed, "%s %s", token1, extra);

            if (scanned_items > MACRO_END_TOKENS) {
                print_external_error(ERROR_CODE_7, current_loc); /* Extra text */
                error_found = TRUE;
            }
            is_inside_macro = FALSE;
            current_mcro_name[0] = '\0';
            continue;
        }

        /* -----------------------------------------------------------------
         * SCENARIO C: Inside a macro body -> Add line to memory
         * ----------------------------------------------------------------- */
        if (is_inside_macro == TRUE) {
            add_macro(&macro_table, current_mcro_name, line);
        }

        /* -----------------------------------------------------------------
         * SCENARIO D: Outside a macro -> Expand or copy verbatim
         * ----------------------------------------------------------------- */
        else {
            char first_word[LINE_BUFFER_SIZE] = "";
            MacroNode *found_macro = NULL;

            sscanf(trimmed, "%s", first_word);
            found_macro = find_macro(macro_table, first_word);

            if (found_macro != NULL) {
                fputs(found_macro->body, out_fp);
            } else {
                fputs(line, out_fp);
            }
        }
    }

    /* Clean up resources */
    fclose(in_fp);
    fclose(out_fp);
    free_macro_table(macro_table);

    /* Delete the incomplete .am file if syntax errors were found */
    if (error_found == TRUE) {
        remove(output_name);
        return FALSE;
    }

    return TRUE;
}