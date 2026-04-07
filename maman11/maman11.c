#include <stdio.h>

int main() {
    /* In ANSI C, declarations MUST come before any executable code */
    int assignment_number = 11;
    // This comment is illegal in ANSI C!
    printf("This push should fail the CI check.\n");
    printf("Hello, Open University!\n");
    printf("Currently working on Maman %d.\n", assignment_number);
    printf("The Ubuntu 24.04 environment is ready.\n");

    return 0;
}