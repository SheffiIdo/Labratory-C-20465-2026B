#ifndef DIFFERENCE_AND_SUM_H
#define DIFFERENCE_AND_SUM_H

/* * CONSTANTS
 * Avoiding 'magic numbers' in the source code
 */
#define PAIR_SIZE 2

/* * MACROS
 * Part B: Macro DIFF calculates the absolute difference.
 * Part C: Macro SUM calculates the sum.
 */
#define SUM(a, b) ((a) + (b))
#define DIFF(a, b) (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))

/*
 * FUNCTION PROTOTYPES
 */
void findDifferenceAndSum(int num1, int num2, int *diff_ptr, int *sum_ptr);
int* saveArray(int *arr, int *size, int num1, int num2);

#endif /* DIFFERENCE_AND_SUM_H */