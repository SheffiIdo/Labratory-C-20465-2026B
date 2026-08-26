#include "../Header files/extern_usage.h"
#include "../Header files/errors.h"
#include "../Header files/globals.h"
#include <stdlib.h>
#include <string.h>

void add_extern_usage(ExternUsageNode **head, const char *name, int address) {
    ExternUsageNode *new_node;
    ExternUsageNode *current;

    /* Allocate memory for the new node */
    new_node = (ExternUsageNode *)malloc(sizeof(ExternUsageNode));
    if (new_node == NULL) {
        memory_allocation_fail = TRUE; /* Failed to allocate memory */
        return;
    }

    /* Populate the node's data */
    strncpy(new_node->name, name, MAX_LABEL_LENGTH);
    new_node->name[MAX_LABEL_LENGTH] = '\0'; /* Ensure null-termination */
    new_node->address = address;
    new_node->next = NULL;

    /* Append to the list */
    if (*head == NULL) {
        /* If the list is empty, this becomes the head */
        *head = new_node;
    } else {
        /* Otherwise, traverse to the very end and attach it */
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void free_extern_usage(ExternUsageNode *head) {
    ExternUsageNode *temp;

    /* Traverse the list and free each node one by one */
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}