#ifndef EXTERN_USAGE_H
#define EXTERN_USAGE_H

#include "../Header files/globals.h"

/**
 * Node for tracking every time an external symbol is used.
 * This is required to build the .ext output file.
 */
typedef struct ExternUsageNode {
    char name[MAX_LABEL_LENGTH];
    int address; /* The IC address where the external symbol was called */
    struct ExternUsageNode *next;
} ExternUsageNode;

/**
 * Adds a new record of an external symbol usage to the tracking list.
 *
 * @param head A pointer to the head pointer of the external usage list.
 * @param name The name of the external symbol being used.
 * @param address The exact memory address (IC) of the instruction making the call.
 */
void add_extern_usage(ExternUsageNode **head, const char *name, int address);

/**
 * Frees all memory allocated for the external usage tracking list.
 *
 * @param head The head pointer of the external usage list.
 */
void free_extern_usage(ExternUsageNode *head);

#endif