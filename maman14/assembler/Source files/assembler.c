#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Header files/globals.h"
#include "../Header files/preproc.h"
#include "../Header files/first_pass.h"
#include "../Header files/second_pass.h"
#include "../Header files/file_writer.h"
#include "../Header files/symbol_table.h"
#include "../Header files/extern_usage.h"

int main(int argc, char *argv[]) {
    int i;
    char as_file[MAX_LINE_LENGTH];
    char base_file[MAX_LINE_LENGTH];
    char am_file[MAX_LINE_LENGTH];
    char *dot_ptr;

    /* Verify the user provided at least one file name */
    if (argc < MINIMUM_ARGS) {
        printf("Error: No input files provided.\n");
        printf("Usage: %s <file1.as> <file2.as> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Iterate forwards through the command-line arguments */
    for (i = 1; i < argc; i++) {
        /*
         * MEMORY ISOLATION:
         * By declaring these inside the loop, we ensure that every single file
         * starts with a completely clean slate.
         */
        SymbolNode *sym_head = NULL;
        ExternUsageNode *ext_head = NULL;
        unsigned char instruction_image[MAX_MEMORY] = {0};
        unsigned char data_image[MAX_MEMORY] = {0};
        int IC = IC_INIT_VALUE;
        int DC = DC_INIT_VALUE;

        printf("ASSEMBLING FILE: %s\n", argv[i]);

        /* Create as_file (Add .as only if it is missing) */
        strcpy(as_file, argv[i]);
        dot_ptr = strrchr(as_file, '.');
        if (dot_ptr == NULL || strcmp(dot_ptr, AS_EXTENSION) != 0) {
            strcat(as_file, AS_EXTENSION);
        }

        /* Create base_file (Start with as_file and chop off the .as) */
        strcpy(base_file, as_file);
        dot_ptr = strrchr(base_file, '.');
        if (dot_ptr != NULL) {
            *dot_ptr = '\0';
        }

        /* Create am_file (Start with base_file and add .am) */
        strcpy(am_file, base_file);
        strcat(am_file, AM_EXTENSION);

        /* PRE-PROCESSOR */
        printf(" Running Pre-Processor...\n");
        if (expand_macros(as_file) == FALSE) {
            printf("Skipping %s due to pre-processor errors.\n", argv[i]);
            continue; /* Move to the next file */
        }

        /* FIRST PASS */
        printf("Running First Pass...\n");
        if (execute_first_pass(am_file, &sym_head, instruction_image, data_image, &IC, &DC) == FALSE) {
            printf("Skipping %s due to First Pass errors.\n", argv[i]);
            free_symbol_table(sym_head); /* Clean up allocated symbols before skipping */
            continue;
        }

        /* SECOND PASS */
        printf("Running Second Pass...\n");
        if (execute_second_pass(am_file, sym_head, &ext_head, instruction_image, &IC) == FALSE) {
            printf("Skipping %s due to Second Pass errors.\n", argv[i]);
            free_symbol_table(sym_head);
            free_extern_usage(ext_head); /* Clean up both lists */
            continue;
        }

        /* FILE WRITER */
        printf("Generating Output Files...\n");
        if (generate_output_files(base_file, IC, DC, instruction_image, data_image, sym_head, ext_head) == FALSE) {
            printf("Failed to generate output files for %s.\n", argv[i]);
            free_symbol_table(sym_head);
            free_extern_usage(ext_head);
            continue;
        }

        /* CLEANUP FOR SUCCESSFUL COMPILATION */
        free_symbol_table(sym_head);
        free_extern_usage(ext_head);

        printf("Finished compiling %s successfully!\n", argv[i]);
    }

    printf("\nEnd of execution.\n");
    return EXIT_SUCCESS;
}