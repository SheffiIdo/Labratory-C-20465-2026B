/*
 * Implements the data structure for storing macro definitions. It handles the
 * safe dynamic allocation, appending, and freeing of macro names and their
 * textual bodies during pre-processing.
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Header files/macro_table.h"
#include "../Header files/globals.h"

MacroNode *find_macro(MacroNode *head, const char *name) {
    MacroNode *current = head;

    /* Traverse the linked list sequentially until the end */
    while (current != NULL) {
        if (strcmp(current->name, name) == STRING_MATCH) {
            return current; /* Match found */
        }
        current = current->next; /* Step forward to the next node */
    }

    return NULL; /* Macro not found in the list */
}

void add_macro(MacroNode **head, const char *name, const char *line_text) {
    MacroNode *existing = find_macro(*head, name);
    size_t old_len;
    size_t line_len;
    char *new_body;
    MacroNode *new_node;

    if (existing != NULL) {
        /* Case 1: macro exists - append text */
        old_len = strlen(existing->body);
        line_len = strlen(line_text);

        /* Reallocate memory to fit existing text and new text */
        new_body = realloc(existing->body, old_len + line_len + NULL_CHAR_LEN);
        if (new_body == NULL) {
            memory_allocation_fail = TRUE;
            return;
        }

        existing->body = new_body;
        strcat(existing->body, line_text);
    }
    else {
        /* Case 2: new macro - create node */
        new_node = malloc(sizeof(MacroNode));
        if (new_node == NULL) {
            memory_allocation_fail = TRUE;
            return;
        }

        /* Allocate exact memory for strings plus the null terminator */
        new_node->name = malloc(strlen(name) + NULL_CHAR_LEN);
        new_node->body = malloc(strlen(line_text) + NULL_CHAR_LEN);

        if (new_node->name == NULL || new_node->body == NULL) {
            if (new_node->name != NULL) {
                free(new_node->name);
            }
            if (new_node->body != NULL) {
                free(new_node->body);
            }
            free(new_node);
            memory_allocation_fail = TRUE;
            return;
        }

        strcpy(new_node->name, name);
        strcpy(new_node->body, line_text);

        /* Insert the new node at the front of the linked list */
        new_node->next = *head;
        *head = new_node;
    }
}

void free_macro_table(MacroNode *head) {
    MacroNode *current = head;
    MacroNode *temp;

    /* Walk through the list and free strings before freeing the node itself */
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->name);
        free(temp->body);
        free(temp);
    }
}

int is_valid_macro_name(const char *name) {
    int i;

    if (name == NULL || name[0] == '\0') {
        return FALSE;
    }

    /* Must start with a letter */
    if (!isalpha((unsigned char)name[0])) {
        return FALSE;
    }

    /* Remaining characters must be letters, numbers, or '_' */
    for (i = 1; name[i] != '\0'; i++) {
        if (!isalnum((unsigned char)name[i]) && name[i] != '_') {
            return FALSE;
        }
    }

    return TRUE;
}