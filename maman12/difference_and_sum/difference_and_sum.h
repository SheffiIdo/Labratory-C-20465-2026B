#ifndef DIFFERENCE_AND_SUM_H
#define DIFFERENCE_AND_SUM_H

/* * MACROS
 * Part B: Macro DIFF calculates the absolute difference[cite: 37].
 * Part C: Macro SUM calculates the sum[cite: 38].
 */
#define SUM(a, b) ((a) + (b))
#define DIFF(a, b) (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))

/*
 * FUNCTION PROTOTYPES
 */

/* * Part A: Calculates the absolute difference and sum of 2 numbers.
 * Receives 2 integers and the addresses of 2 variables to store the results[cite: 25, 27].
 */
void findDifferenceAndSum(int num1, int num2, int *diff_ptr, int *sum_ptr);

/* * Part D: Saves the pairs of numbers in a dynamic array.
 * Uses realloc to grow the array as needed[cite: 40].
 * We return an integer pointer to the dynamically allocated array.
 */
int* saveArray(int *arr, int *size, int num1, int num2);

#endif /* DIFFERENCE_AND_SUM_H */