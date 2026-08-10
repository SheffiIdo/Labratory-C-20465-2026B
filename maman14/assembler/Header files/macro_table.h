#ifndef MACRO_TABLE_H
#define MACRO_TABLE_H

/* Structure to represent a single macro definition node */
typedef struct MacroNode {
    char *name;               /* Dynamically allocated macro name */
    char *body;               /* Dynamically allocated macro lines */
    struct MacroNode *next;   /* Pointer to the next macro node in the list */
} MacroNode;

/*
 * Functions for the macro storage engine
 */

/**
 * Adds a new macro to the list, or appends a line of text to an existing macro's body.
 * Handles all dynamic memory scaling automatically.
 * @param head a double pointer to the head of the macro linked list
 * @param name the string identifier of the macro
 * @param line_text the text line to append to the macro's body
 */
void add_macro(MacroNode **head, const char *name, const char *line_text);

/**
 * Iterates through the linked list to find a macro by its name.
 * @param head a pointer to the head of the macro linked list
 * @param name the string identifier of the macro to find
 * @return a pointer to the MacroNode if found, or NULL if it does not exist
 */
MacroNode *find_macro(MacroNode *head, const char *name);

/**
 * Frees all dynamically allocated memory within the macro table
 * to prevent memory leaks.
 * @param head a pointer to the head of the macro linked list
 */
void free_macro_table(MacroNode *head);

#endif /* MACRO_TABLE_H */