/*
 * Manages a dynamic linked list that tracks all user-defined labels. It records
 * each label's calculated memory address alongside its specific attributes
 * (code, data, entry, or extern).
 */

#include <string.h>
#include <stdlib.h>
#include "../Header files/symbol_table.h"

SymbolNode *find_symbol(SymbolNode *head, const char *name) {
    SymbolNode *current = head;

    /* Traverse the linked list until a match is found or the end is reached */
    while (current != NULL) {
        if (strcmp(current->name, name) == STRING_MATCH) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void add_symbol(SymbolNode **head, const char *name, int address, SymbolAttribute attribute) {
    SymbolNode *new_node;
    SymbolNode *current;

    /* Allocate memory and handle potential allocation failure */
    new_node = (SymbolNode *)malloc(sizeof(SymbolNode));
    if (new_node == NULL) {
        memory_allocation_fail = TRUE;
        return;
    }

    /* Initialize the basic data of the new symbol node */
    strcpy(new_node->name, name);
    new_node->address = address;
    new_node->is_code = FALSE;
    new_node->is_data = FALSE;
    new_node->is_extern = FALSE;
    new_node->is_entry = FALSE;
    new_node->next = NULL;

    /* Set the specific boolean flag based on the provided attribute */
    if (attribute == CODE_SYMBOL) {
        new_node->is_code = TRUE;
    } else if (attribute == DATA_SYMBOL) {
        new_node->is_data = TRUE;
    } else if (attribute == EXTERN_SYMBOL) {
        new_node->is_extern = TRUE;
    }

    /* Insert the new node at the end of the existing list */
    if (*head == NULL) {
        *head = new_node;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

int mark_as_entry(SymbolNode *head, const char *name) {
    SymbolNode *node = find_symbol(head, name);

    /* If the symbol exists, toggle its entry flag to true */
    if (node != NULL) {
        node->is_entry = TRUE;
        return TRUE;
    }

    return FALSE;
}

void update_data_symbols_address(SymbolNode *head, int final_ic) {
    SymbolNode *current = head;

    /* Shift the address of all data symbols by adding the final IC value */
    while (current != NULL) {
        if (current->is_data == TRUE) {
            current->address += final_ic;
        }
        current = current->next;
    }
}

void free_symbol_table(SymbolNode *head) {
    SymbolNode *temp;

    /* Iterate through the list and free each node sequentially */
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}