#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Header files/globals.h"
#include "../Header files/preproc.h"

int main(int argc, char *argv[]) {
    int i;

    /* Verify the user provided at least one file name */
    if (argc < 2) {
        printf("Error: No input files provided.\n");
        printf("Usage: %s <file1.as> <file2.as> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Iterate forwards through the command-line arguments */
    for (i = 1; i < argc; i++) {

        printf("\n==================================================\n");
        printf(" ASSEMBLING FILE: %s\n", argv[i]);
        printf("==================================================\n");

        /* --- PHASE 1: PRE-PROCESSOR --- */
        printf("Start pre-proc\n");

        /* argv[i] already contains the ".as", so we pass it directly */
        if (expand_macros(argv[i]) == FALSE) {
            /* Error messages were already printed by the error engine */
            printf("Skipping %s due to pre-processor errors.\n", argv[i]);
            continue; /* Safely move to the next file */
        }

        /*
         * --- FUTURE WORK: FIRST PASS ---
         * Here, you will swap the ".as" in argv[i] to ".am" (similar to your friend's add_new_file),
         * pass it to the first pass, and remember to free it!
         *
         * printf("Start first pass\n");
         * char *am_file = swap_extension(argv[i], ".am");
         * if (first_pass(am_file) == FALSE) {
         *     free(am_file);
         *     continue;
         * }
         *
         * --- FUTURE WORK: SECOND PASS ---
         * printf("Start second pass\n");
         * if (second_pass(am_file) == FALSE) {
         *     free(am_file);
         *     continue;
         * }
         *
         * free(am_file); // Safely free it at the very end if everything succeeds
         */

         printf("Finished compiling %s successfully!\n", argv[i]);
    }

    printf("\nEnd of execution.\n");
    return EXIT_SUCCESS;
}