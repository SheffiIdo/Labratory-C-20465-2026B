#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Header files/preproc.h"
#include "../Header files/macro_table.h"
#include "../Header files/errors.h"
#include "../Header files/utils.h"

int expand_macros(const char *filename) {
    /* All variable declarations */
    char *output_name = NULL;
    char line[LINE_BUFFER_SIZE];
    char trimmed[LINE_BUFFER_SIZE];
    char current_mcro_name[MAX_LABEL_LENGTH + NULL_CHAR_LEN] = "";
    char token1[LINE_BUFFER_SIZE];
    char token2[LINE_BUFFER_SIZE];
    char extra[LINE_BUFFER_SIZE];

    FILE *in_fp = NULL;
    FILE *out_fp = NULL;
    MacroNode *macro_table = NULL;

    int is_inside_macro = FALSE;
    int error_found = FALSE;
    int line_counter = 0;
    int scanned_items = 0;
    size_t name_len;
    size_t ext_len;


    location current_loc;

    /* Calculate the file name and replace ".as" with ".am" */
    name_len = strlen(filename);
    ext_len = strlen(AS_EXTENSION);

    output_name = malloc(name_len + strlen(AM_EXTENSION) + NULL_CHAR_LEN);
    if (output_name == NULL) {
        print_internal_error(ERROR_CODE_1);
        return FALSE;
    }

    strcpy(output_name, filename);

    if (name_len >= ext_len && strcmp(output_name + name_len - ext_len, AS_EXTENSION) == STRING_MATCH) {
        /* Overwrite exactly the ".as" with ".am" at the end of the string */
        strcpy(output_name + name_len - ext_len, AM_EXTENSION);
    } else {
        /* If it doesn't end in .as, just safely append .am */
        strcat(output_name, AM_EXTENSION);
    }

    /* Set up the location tracker for our error engine */
    current_loc.file_name = (char *)filename;

    /* Attempt to open the source file using the provided pointer */
    in_fp = fopen(filename, "r");
    if (in_fp == NULL) {
        print_internal_error(ERROR_CODE_2);
        free(output_name);
        return FALSE;
    }

    /* Attempt to open the target file */
    out_fp = fopen(output_name, "w");
    if (out_fp == NULL) {
        print_internal_error(ERROR_CODE_3);
        fclose(in_fp);
        free(output_name);
        return FALSE;
    }

    /* Process the file line-by-line */
    while (fgets(line, sizeof(line), in_fp) != NULL) {
        line_counter++;
        current_loc.line_num = line_counter;

        /* Check for lines exceeding the 80 character limit */
        if (strchr(line, '\n') == NULL && !feof(in_fp)) {
            print_external_error(ERROR_CODE_4, current_loc);
            error_found = TRUE;
            while (fgets(line, sizeof(line), in_fp) != NULL && strchr(line, '\n') == NULL);
            continue;
        }

        trim_leading_whitespace(trimmed, line);

        /* Ignore empty lines and comment lines entirely */
        if (trimmed[0] == '\0' || trimmed[0] == COMMENT_CHAR) {
            continue;
        }

        /*
         * Check for start of macro ("mcro <name>")
         */
        if (strncmp(trimmed, MACRO_START_TOKEN, strlen(MACRO_START_TOKEN)) == STRING_MATCH &&
            isspace((unsigned char)trimmed[strlen(MACRO_START_TOKEN)])) {

            /* Catch macros declared inside other macros */
            if (is_inside_macro == TRUE) {
                print_external_error(ERROR_CODE_11, current_loc);
                error_found = TRUE;
                continue; /* Keep parsing, but don't process this inner macro */
            }

            scanned_items = sscanf(trimmed, "%s %s %s", token1, token2, extra);

            if (scanned_items < MACRO_DEF_TOKENS) {
                print_external_error(ERROR_CODE_5, current_loc);
                error_found = TRUE;
            }
            else if (scanned_items > MACRO_DEF_TOKENS) {
                print_external_error(ERROR_CODE_6, current_loc);
                error_found = TRUE;
            }
            else if (is_reserved_word(token2) == TRUE) {
                print_external_error(ERROR_CODE_8, current_loc);
                error_found = TRUE;
            }
            else if (find_macro(macro_table, token2) != NULL) {
                print_external_error(ERROR_CODE_9, current_loc);
                error_found = TRUE;
            }
            else {
                is_inside_macro = TRUE;
                strcpy(current_mcro_name, token2);
            }
            continue;
        }

        /* -----------------------------------------------------------------
         * CHECK FOR END OF MACRO ("mcroend")
         * ----------------------------------------------------------------- */
        if (strncmp(trimmed, MACRO_END_TOKEN, strlen(MACRO_END_TOKEN)) == STRING_MATCH &&
           (isspace((unsigned char)trimmed[strlen(MACRO_END_TOKEN)]) || trimmed[strlen(MACRO_END_TOKEN)] == '\0')) {

            scanned_items = sscanf(trimmed, "%s %s", token1, extra);

            if (scanned_items > MACRO_END_TOKENS) {
                print_external_error(ERROR_CODE_7, current_loc);
                error_found = TRUE;
            }

            is_inside_macro = FALSE;
            current_mcro_name[0] = '\0';
            continue;
           }

        /*
         * Handle standard lines or macro body content
          */
        if (is_inside_macro == TRUE) {
            add_macro(&macro_table, current_mcro_name, line);
        }
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

    /* Check if the file ended while a macro was still open */
    if (is_inside_macro == TRUE) {
        print_external_error(ERROR_CODE_12, current_loc);
        error_found = TRUE;
    }

    /* Clean up resources */
    fclose(in_fp);
    fclose(out_fp);
    free_macro_table(macro_table);

    /* If syntax errors were found, the .am file is corrupted. Delete it. */
    if (error_found == TRUE) {
        remove(output_name);
        free(output_name);
        return FALSE;
    }

    free(output_name);
    return TRUE;
}