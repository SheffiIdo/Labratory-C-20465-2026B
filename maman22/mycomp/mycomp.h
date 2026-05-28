#ifndef MYCOMP_H
#define MYCOMP_H

#include "complex.h"

/* --- CONFIGURATION MACROS --- */
#define MAX_LINE 100

/* Single parameter commands */
#define PARAMS_SINGLE 1
#define PARSED_GARBAGE_SINGLE 2

/* Dual parameter commands */
#define PARAMS_DUAL 2
#define COMMAS_DUAL 1
#define PARSED_GARBAGE_DUAL 3

/* Triple parameter commands */
#define PARAMS_TRIPLE 3
#define COMMAS_TRIPLE 2
#define PARSED_GARBAGE_TRIPLE 4


/* --- HELPER FUNCTION PROTOTYPES --- */
void stop_comp(int *running_state);

complex* get_variable(char var_name, complex *A, complex *B, complex *C, complex *D, complex *E, complex *F);

int validate_commas(char *args, int expected_commas);
int count_tokens(char *args);

#endif /* MYCOMP_H */