#include <ctype.h>
#include <string.h>
#include "../Header files/utils.h"
#include "../Header files/globals.h"

void trim_leading_whitespace(char *output, const char *input) {
    while (isspace((unsigned char)*input)) {
        input++;
    }
    strcpy(output, input);
}

int is_reserved_word(const char *name) {
    if (strcmp(name, "add") == STRING_MATCH || strcmp(name, "sub") == STRING_MATCH ||
        strcmp(name, "and") == STRING_MATCH || strcmp(name, "or") == STRING_MATCH ||
        strcmp(name, "nor") == STRING_MATCH || strcmp(name, "move") == STRING_MATCH ||
        strcmp(name, "mvhi") == STRING_MATCH || strcmp(name, "mvlo") == STRING_MATCH ||
        strcmp(name, "addi") == STRING_MATCH || strcmp(name, "subi") == STRING_MATCH ||
        strcmp(name, "andi") == STRING_MATCH || strcmp(name, "ori") == STRING_MATCH ||
        strcmp(name, "nori") == STRING_MATCH || strcmp(name, "bne") == STRING_MATCH ||
        strcmp(name, "beq") == STRING_MATCH || strcmp(name, "blt") == STRING_MATCH ||
        strcmp(name, "bgt") == STRING_MATCH || strcmp(name, "lb") == STRING_MATCH ||
        strcmp(name, "sb") == STRING_MATCH || strcmp(name, "lw") == STRING_MATCH ||
        strcmp(name, "sw") == STRING_MATCH || strcmp(name, "lh") == STRING_MATCH ||
        strcmp(name, "sh") == STRING_MATCH || strcmp(name, "jmp") == STRING_MATCH ||
        strcmp(name, "la") == STRING_MATCH || strcmp(name, "call") == STRING_MATCH ||
        strcmp(name, "hlt") == STRING_MATCH ||
        strcmp(name, ".db") == STRING_MATCH || strcmp(name, ".dh") == STRING_MATCH ||
        strcmp(name, ".dw") == STRING_MATCH || strcmp(name, ".asciz") == STRING_MATCH ||
        strcmp(name, ".entry") == STRING_MATCH || strcmp(name, ".extern") == STRING_MATCH ||
        strcmp(name, "mcro") == STRING_MATCH || strcmp(name, "mcroend") == STRING_MATCH) {

        return TRUE;
        }

    return FALSE;
}

void skip_whitespace(char **str) {
    /* Advance the pointer as long as the character is a space or tab */
    while (**str != '\0' && (**str == ' ' || **str == '\t')) {
        (*str)++;
    }
}