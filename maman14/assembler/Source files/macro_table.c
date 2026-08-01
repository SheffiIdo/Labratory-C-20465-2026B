#include <stdlib.h>
#include <string.h>
#include "../Header files/macro_table.h"
#include "../Header files/errors.h"

/* =========================================================================
 * FUNCTION: find_macro
 * PURPOSE: Iterates through the linked list to find a macro by its name.
 * RETURNS: Pointer to the MacroNode if found, or NULL if it does not exist.
 * ========================================================================= */
MacroNode *find_macro(MacroNode *head, const char *name) {
    MacroNode *current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == STRING_MATCH) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

/* =========================================================================
 * FUNCTION: add_macro
 * PURPOSE: Adds a new macro to the list, or appends a line of text to an
 *          existing macro's body. Handles all dynamic memory scaling.
 * ========================================================================= */
void add_macro(MacroNode **head, const char *name, const char *line_text) {
    /* C90 standard requires all variable declarations at the top */
    MacroNode *existing = find_macro(*head, name);
    size_t old_len;
    size_t line_len;
    char *new_body;
    MacroNode *new_node;

    if (existing != NULL) {
        /* CASE 1: MACRO EXISTS - APPEND TEXT */
        old_len = strlen(existing->body);
        line_len = strlen(line_text);

        new_body = realloc(existing->body, old_len + line_len + NULL_CHAR_LEN);
        if (new_body == NULL) {
            print_internal_error(ERROR_CODE_1);
        }

        existing->body = new_body;
        strcat(existing->body, line_text);
    }
    else {
        /* CASE 2: NEW MACRO - CREATE NODE */
        new_node = malloc(sizeof(MacroNode));
        if (new_node == NULL) {
            print_internal_error(ERROR_CODE_1);
        }

        new_node->name = malloc(strlen(name) + NULL_CHAR_LEN);
        new_node->body = malloc(strlen(line_text) + NULL_CHAR_LEN);

        if (new_node->name == NULL || new_node->body == NULL) {
            print_internal_error(ERROR_CODE_1);
        }

        strcpy(new_node->name, name);
        strcpy(new_node->body, line_text);

        new_node->next = *head;
        *head = new_node;
    }
}

/* =========================================================================
 * FUNCTION: free_macro_table
 * PURPOSE: Safely frees all dynamically allocated memory in the macro table.
 * ========================================================================= */
void free_macro_table(MacroNode *head) {
    MacroNode *current = head;
    MacroNode *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;

        free(temp->name);
        free(temp->body);
        free(temp);
    }
}