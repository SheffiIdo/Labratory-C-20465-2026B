#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "../Header files/globals.h"

/* A node in the Symbol Table linked list */
typedef struct SymbolNode {
    char name[MAX_LABEL_LENGTH + 1];
    int address;
    /* Boolean flags for attributes (1 for TRUE, 0 for FALSE) */
    int is_code;
    int is_data;
    int is_extern;
    int is_entry;

    struct SymbolNode *next;
} SymbolNode;

/**
 * Searches for a symbol by name in the symbol table.
 * @param head Pointer to the head of the symbol table
 * @param name The name of the label to find
 * @return A pointer to the SymbolNode if found, NULL otherwise
 */
SymbolNode *find_symbol(SymbolNode *head, const char *name);

/**
 * Adds a new symbol to the end of the symbol table.
 * @param head Pointer to the pointer of the head of the symbol table
 * @param name The label name
 * @param address The memory address (IC or DC)
 * @param attribute The primary attribute (CODE_SYMBOL, DATA_SYMBOL, or EXTERN_SYMBOL)
 */
void add_symbol(SymbolNode **head, const char *name, int address, SymbolAttribute attribute);

/**
 * Marks an existing symbol as an entry symbol.
 * @param head Pointer to the head of the symbol table
 * @param name The name of the label to mark as entry
 * @return true (1) if successful, false (0) if the symbol was not found
 */
int mark_as_entry(SymbolNode *head, const char *name);

/**
 * Updates the addresses of all data symbols by adding the final IC to them.
 * This is called exactly once at the very end of the First Pass.
 * @param head Pointer to the head of the symbol table
 * @param final_ic The final Instruction Counter value after the First Pass
 */
void update_data_symbols_address(SymbolNode *head, int final_ic);

/**
 * Frees all memory allocated for the symbol table.
 * @param head Pointer to the head of the symbol table
 */
void free_symbol_table(SymbolNode *head);

#endif