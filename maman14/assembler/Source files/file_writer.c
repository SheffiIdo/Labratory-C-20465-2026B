#include "../Header files/file_writer.h"
#include "../Header files/errors.h"
#include <stdio.h>
#include <string.h>

/* --- Private Helper Function Declarations --- */
static int write_ob_file(const char *base_file_name, int ICF, int DCF, unsigned char instruction_image[], unsigned char data_image[]);
static int write_ent_file(const char *base_file_name, SymbolNode *sym_head);
static int write_ext_file(const char *base_file_name, ExternUsageNode *ext_head);

/* --- Main File Writer Execution --- */
int generate_output_files(const char *base_file_name, int ICF, int DCF, unsigned char instruction_image[], unsigned char data_image[], SymbolNode *sym_head, ExternUsageNode *ext_head) {

    /* Generate .ob file */
    if (write_ob_file(base_file_name, ICF, DCF, instruction_image, data_image) == FALSE) {
        print_internal_error(ERROR_CODE_3); /* Cannot open file for writing */
        return FALSE;
    }

    /* Generate .ent file - Only created if needed */
    if (write_ent_file(base_file_name, sym_head) == FALSE) {
        print_internal_error(ERROR_CODE_3);
        return FALSE;
    }

    /* Generate .ext file - Only created if needed */
    if (write_ext_file(base_file_name, ext_head) == FALSE) {
        print_internal_error(ERROR_CODE_3);
        return FALSE;
    }

    return TRUE;
}

/* --- Private Helper Implementations --- */

/*
 * Writes the machine code image to the .ob file.
 * Formats addresses as 4-digit decimals, and bytes as 2-digit Hex.
 */
static int write_ob_file(const char *base_file_name, int ICF, int DCF, unsigned char instruction_image[], unsigned char data_image[]) {
    FILE *file;
    char file_name[MAX_LINE_LENGTH];
    int address = IC_INIT_VALUE;
    int i, j;
    int instruction_count = ICF - IC_INIT_VALUE;

    sprintf(file_name, "%s%s", base_file_name, OB_EXTENSION);
    file = fopen(file_name, "w");
    if (file == NULL) {
        return FALSE;
    }

    /* Print header: Code Size, Data Size */
    fprintf(file, "     %d %d\n", instruction_count, DCF);

    /* Print Instructions */
    for (i = 0; i < instruction_count; i += BYTES_PER_INSTRUCTION) {
        fprintf(file, "%04d %02X %02X %02X %02X\n",
                address,
                instruction_image[address + BYTE_OFFSET_0],
                instruction_image[address + BYTE_OFFSET_1],
                instruction_image[address + BYTE_OFFSET_2],
                instruction_image[address + BYTE_OFFSET_3]);
        address += BYTES_PER_INSTRUCTION;
    }

    /* Print Data, continues after instructions */
    for (i = 0; i < DCF; i += BYTES_PER_INSTRUCTION) {
        fprintf(file, "%04d", address);

        /* Prints up to 4 bytes. If less than 4 bytes remain, it stops early gracefully */
        for (j = 0; j < BYTES_PER_INSTRUCTION && (i + j) < DCF; j++) {
            fprintf(file, " %02X", data_image[i + j]);
        }
        fprintf(file, "\n");
        address += BYTES_PER_INSTRUCTION;
    }

    fclose(file);
    return TRUE;
}

/*
 * Scans the symbol table for any .entry symbols.
 * If one is found, it creates the .ent file and writes it.
 * If no entries exist, the file is never created.
 */
static int write_ent_file(const char *base_file_name, SymbolNode *sym_head) {
    FILE *file = NULL;
    char file_name[MAX_LINE_LENGTH];
    SymbolNode *curr = sym_head;
    int file_created = FALSE;

    while (curr != NULL) {
        if (curr->is_entry == TRUE) {
            /* Create file only when the first entry is discovered */
            if (file_created == FALSE) {
                sprintf(file_name, "%s%s", base_file_name, ENT_EXTENSION);
                file = fopen(file_name, "w");
                if (file == NULL) {
                    return FALSE;
                }
                file_created = TRUE;
            }
            fprintf(file, "%s %04d\n", curr->name, curr->address);
        }
        curr = curr->next;
    }

    if (file != NULL) {
        fclose(file);
    }
    return TRUE;
}

/*
 * Iterates through the tracking list of external symbol usages.
 * If the list is empty, it returns immediately without creating a file.
 */
static int write_ext_file(const char *base_file_name, ExternUsageNode *ext_head) {
    FILE *file;
    char file_name[MAX_LINE_LENGTH];
    ExternUsageNode *curr = ext_head;

    /* If no external symbols were used, don't create the file */
    if (curr == NULL) {
        return TRUE;
    }

    sprintf(file_name, "%s%s", base_file_name, EXT_EXTENSION);
    file = fopen(file_name, "w");
    if (file == NULL) {
        return FALSE;
    }

    while (curr != NULL) {
        fprintf(file, "%s %04d\n", curr->name, curr->address);
        curr = curr->next;
    }

    fclose(file);
    return TRUE;
}