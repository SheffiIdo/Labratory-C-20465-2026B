/*
* Name: Ido Sheffi
* ID: 208138974
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"

#define MAX_LINE 100 /* A generous buffer for user input lines */

/* Helper functions Prototypes */
void stop_comp(int *running_state);
complex* get_variable(char var_name, complex *A, complex *B, complex *C, complex *D, complex *E, complex *F);
int validate_commas(char *args, int expected_commas);
int count_tokens(char *args);

int main(void) {
    /* Define and initialize the 6 required variables to 0 + 0i */
    complex A = {0.0, 0.0};
    complex B = {0.0, 0.0};
    complex C = {0.0, 0.0};
    complex D = {0.0, 0.0};
    complex E = {0.0, 0.0};
    complex F = {0.0, 0.0};

    char line[MAX_LINE];
    int is_running = 1; /* State flag: 1 means running, 0 means stop */

    printf("--- Welcome to the Complex Number Calculator ---\n");
    printf("Valid variables are A, B, C, D, E, F.\n");

    /* The Loop depends entirely on the state flag. */
    while (is_running) {
        printf("\nEnter command > ");

        /* Read the line. If it fails (EOF), handle it gracefully */
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            printf("\nError: Reached End Of File (EOF) without 'stop' command.\n");
            is_running = 0; /* Turn off the loop naturally */
        } else {
            /* Print the line back to the user exactly as read */
            char cmd_name[MAX_LINE];
            int chars_read = 0;
            char *args;
            printf("%s", line); /* Print the exact input */

            /* If the file ends with EOF, the line won't have a newline.
             * This ensures our output format always stays clean.
             */
            if (strchr(line, '\n') == NULL) {
                printf("\n");
            }

            /* sscanf reads the first word into cmd_name.
             * %n stores the number of characters read into chars_read.
             * If sscanf returns EOF or 0, the line was just blank spaces.
             */
            if (sscanf(line, "%s%n", cmd_name, &chars_read) != 1) {
                continue; /* User just pressed Enter, ask for input again */
            }

            /* Catch commas glued to the command name --- */
            if (strchr(cmd_name, ',') != NULL) {
                printf("Illegal comma\n");
                continue;
            }

            /* Create a pointer that points to exactly where the command name finished.
             * We will pass this to our helper functions later to check for variables and commas.
             */
            args = line + chars_read;

            /* ==========================================
             * ROUTE THE COMMAND
             * ========================================== */
            if (strcmp(cmd_name, "read_comp") == 0) {
                /* --- THREE VARIABLE COMMAND (1 Char, 2 Doubles) --- */
                /* Declarations the variables */
                char var_name;
                double val_real, val_imag;
                char garbage[MAX_LINE];
                complex *target_var;
                int parsed_items;
                int tokens = count_tokens(args);

                /* Check params first */
                if (tokens < 3) {
                    printf("Missing parameter\n");
                    continue;
                }

                /* read_comp requires exactly 2 commas */
                if (!validate_commas(args, 2)) {
                    continue;
                }

                /* %lf used for parsing double variables */
                parsed_items = sscanf(args, " %c , %lf , %lf %s", &var_name, &val_real, &val_imag, garbage);

                if (parsed_items < 3) {
                    /* If we have 2 commas but couldn't get 3 items, they typed letters instead of numbers */
                    printf("Invalid parameter - not a number\n");
                } else {
                    target_var = get_variable(var_name, &A, &B, &C, &D, &E, &F);

                    /* Check variable first, then check garbage */
                    if (target_var == NULL) {
                        printf("Undefined complex variable\n");
                    } else if (parsed_items == 4) {
                        printf("Extraneous text after end of command\n");
                    } else {
                        /* Everything is valid, Call read_comp.*/
                        read_comp(target_var, val_real, val_imag);
                    }
                }

            } else if (strcmp(cmd_name, "print_comp") == 0 || strcmp(cmd_name, "abs_comp") == 0) {
                /* --- SINGLE VARIABLE COMMANDS --- */
                char var_name;
                char garbage[MAX_LINE];
                complex *target_var;
                int parsed_items;
                int tokens = count_tokens(args);

                /* Check params first */
                if (tokens < 1) {
                    printf("Missing parameter\n");
                    continue;
                }

                parsed_items = sscanf(args, " %c %s", &var_name, garbage);

                if (parsed_items == EOF || parsed_items == 0) {
                    printf("Missing parameter\n");
                } else {
                    target_var = get_variable(var_name, &A, &B, &C, &D, &E, &F);

                    /* Check variable first, then check garbage */
                    if (target_var == NULL) {
                        printf("Undefined complex variable\n");
                    } else if (parsed_items == 2) {
                        printf("Extraneous text after end of command\n");
                    } else {
                        /* Everything is valid, execute the math! */
                        if (strcmp(cmd_name, "print_comp") == 0) {
                            print_comp(*target_var);
                        } else {
                            printf("%.2f\n", abs_comp(*target_var));
                        }
                    }
                }

            } else if (strcmp(cmd_name, "add_comp") == 0 ||
                       strcmp(cmd_name, "sub_comp") == 0 ||
                       strcmp(cmd_name, "mult_comp_comp") == 0) {

                /* --- TWO VARIABLE COMMANDS --- */
                /* Parse the variables */
                char var1_name, var2_name;
                char garbage[MAX_LINE];
                complex *target_var1, *target_var2;
                int parsed_items;
                int tokens = count_tokens(args);

                /* Check params first */
                if (tokens < 2) {
                    printf("Missing parameter\n");
                    continue;
                }

                /* Pre-validate commas (We expect exactly 1 comma) */
                if (!validate_commas(args, 1)) {
                    continue; /* Error was already printed, skip to next line */
                }


                parsed_items = sscanf(args, " %c , %c %s", &var1_name, &var2_name, garbage);

                if (parsed_items == EOF || parsed_items < 2) {
                    printf("Missing parameter\n");
                } else {
                    target_var1 = get_variable(var1_name, &A, &B, &C, &D, &E, &F);
                    target_var2 = get_variable(var2_name, &A, &B, &C, &D, &E, &F);

                    /* Check variable first, then check garbage */
                    if (target_var1 == NULL || target_var2 == NULL) {
                        printf("Undefined complex variable\n");
                    } else if (parsed_items == 3) {
                        printf("Extraneous text after end of command\n");
                    } else {
                        /* Everything is valid! Execute the math. */
                        if (strcmp(cmd_name, "add_comp") == 0) {
                            print_comp(add_comp(*target_var1, *target_var2));
                        } else if (strcmp(cmd_name, "sub_comp") == 0) {
                            print_comp(sub_comp(*target_var1, *target_var2));
                        } else if (strcmp(cmd_name, "mult_comp_comp") == 0) {
                            print_comp(mult_comp_comp(*target_var1, *target_var2));
                        }
                    }
                }
            } else if (strcmp(cmd_name, "mult_comp_real") == 0 || strcmp(cmd_name, "mult_comp_img") == 0) {
                /* --- VAR + NUMBER COMMANDS --- */
                /* Declarations first */
                char var_name;
                double multiplier;
                char garbage[MAX_LINE];
                complex *target_var;
                int parsed_items;
                int tokens = count_tokens(args);

                /* Check params first */
                if (tokens < 2) {
                printf("Missing parameter\n");
                continue;
                }

                /* These commands require exactly 1 comma */
                if (!validate_commas(args, 1)) {
                    continue;
                }

                parsed_items = sscanf(args, " %c , %lf %s", &var_name, &multiplier, garbage);

                if (parsed_items < 2) {
                    printf("Invalid parameter - not a number\n");
                } else {
                    target_var = get_variable(var_name, &A, &B, &C, &D, &E, &F);

                    /* NEW ORDER: Check variable first, then check garbage */
                    if (target_var == NULL) {
                        printf("Undefined complex variable\n");
                    } else if (parsed_items == 3) {
                        printf("Extraneous text after end of command\n");
                    } else {
                        if (strcmp(cmd_name, "mult_comp_real") == 0) {
                            print_comp(mult_comp_real(*target_var, multiplier));
                        } else {
                            print_comp(mult_comp_img(*target_var, multiplier));
                        }
                    }
                }
            } else if (strcmp(cmd_name, "stop") == 0) {
                char garbage[MAX_LINE];

                if (sscanf(args, " %s", garbage) == 1) {
                    printf("Extraneous text after end of command\n");
                } else {
                    stop_comp(&is_running);
                }

            } else {
                /* If it doesn't match any of the above, it's an illegal command */
                printf("Undefined command name\n");
            }
        }
    }

    return 0;
}

/* =========================================================================
 * HELPER FUNCTIONS
 * ========================================================================= */
void stop_comp(int *running_state) {
    *running_state = 0;
}

complex* get_variable(char var_name, complex *A, complex *B, complex *C, complex *D, complex *E, complex *F) {
    if (var_name == 'A') return A;
    if (var_name == 'B') return B;
    if (var_name == 'C') return C;
    if (var_name == 'D') return D;
    if (var_name == 'E') return E;
    if (var_name == 'F') return F;
    return NULL;
}

/*
 * Purpose: Scans the argument string to catch all comma-related syntax errors.
 * Returns 1 if commas are valid, 0 if an error was printed.
*/
int validate_commas(char *args, int expected_commas) {
    int i;
    int comma_count = 0;
    int comma_in_a_row = 0;
    int has_chars = 0;
    int last_char_was_comma = 0;

    for (i = 0; args[i] != '\0'; i++) {
        /* Skip over any whitespace */
        if (args[i] == ' ' || args[i] == '\t' || args[i] == '\n') {
            continue;
        }

        if (args[i] == ',') {
            comma_count++;

            if (comma_in_a_row) {
                printf("Multiple consecutive commas\n");
                return 0;
            }
            if (!has_chars) {
                printf("Illegal comma\n"); /* e.g., command starts with a comma */
                return 0;
            }

            comma_in_a_row = 1;
            last_char_was_comma = 1;
        } else {
            comma_in_a_row = 0; /* Reset flag when we hit a normal character */
            has_chars = 1;
            last_char_was_comma = 0;
        }
    }

    if (last_char_was_comma) {
        printf("Extraneous text after end of command\n"); /* Ended with a comma */
        return 0;
    }

    if (comma_count < expected_commas) {
        printf("Missing comma\n");
        return 0;
    }

    return 1; /* Commas are perfect! */
}

/*
 * Purpose: Counts the number of parameters provided, ignoring commas and spaces
 * to catch "Missing parameter" errors first.
 */
int count_tokens(char *args) {
    int count = 0;
    int in_token = 0;
    int i;
    for (i = 0; args[i] != '\0'; i++) {
        if (args[i] == ' ' || args[i] == '\t' || args[i] == '\n' || args[i] == ',') {
            in_token = 0;
        } else {
            if (!in_token) {
                count++;
                in_token = 1;
            }
        }
    }
    return count;
}