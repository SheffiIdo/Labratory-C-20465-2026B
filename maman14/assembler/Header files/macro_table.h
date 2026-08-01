#ifndef MACRO_TABLE_H
#define MACRO_TABLE_H

#include "../Header files/globals.h"

/* Structure to represent a single macro definition node */
typedef struct MacroNode {
    char *name;               /* Dynamically allocated macro name */
    char *body;               /* Dynamically allocated macro lines */
    struct MacroNode *next;   /* Pointer to the next macro node in the list */
} MacroNode;

/* =========================================================================
 * INTERFACE FUNCTIONS FOR THE MACRO STORAGE ENGINE
 * ========================================================================= */

/* Adds a new macro or appends text lines to an existing macro definition */
void add_macro(MacroNode **head, const char *name, const char *line_text);

/* Looks up a macro by its name. Returns the node if found, otherwise NULL */
MacroNode *find_macro(MacroNode *head, const char *name);

/* Completely frees all dynamically allocated memory within the macro table */
void free_macro_table(MacroNode *head);

#endif /* MACRO_TABLE_H */