#include <stdio.h>
#include <stdlib.h> /* Required for realloc(), free(), and exit() */
#include "difference_and_sum.h" /* Our custom header file */

int main(void) {
    int num1, num2;
    int num1_copy, num2_copy; /* The sacrificial copies for the function */
    int sum_mac, diff_mac;

    /* pairs_array will point to our dynamically resizing array.
     * We initialize it to NULL so realloc knows it's the first allocation.
     */
    int *pairs_array = NULL;
    int total_numbers = 0; /* Keeps track of how many total ints are in the array */
    int i;

    printf("Welcome to the Difference and Sum Calculator!\n");
    printf("Please enter pairs of integers (e.g., '1 3').\n");
    printf("Press Ctrl+D (or Ctrl+Z on Windows) to stop reading input.\n");

    /* scanf returns the number of items successfully read.
     * We compare it against PAIR_SIZE.
     */
    while (scanf("%d %d", &num1, &num2) == PAIR_SIZE) {
        /* IMMEDIATELY create copies for the function to consume/destroy */
        num1_copy = num1;
        num2_copy = num2;

        printf("\n--- Processing Pair: %d and %d ---\n", num1, num2);

        /* THE "BEFORE" PRINT */
        printf("Function (Before): num1_copy is %d, num2_copy is %d\n", num1_copy, num2_copy);

        /* Send the copies and their addresses to the function */
        findDifferenceAndSum(num1_copy, num2_copy, &num1_copy, &num2_copy);

        /* THE "AFTER" PRINT
         * Note: num1_copy now holds the sum, and num2_copy holds the difference.
         */
        printf("Function (After):  num1_copy (sum) is %d : num2_copy (diff) is %d\n", num1_copy, num2_copy);

        /* Calculate using the Macros */
        sum_mac = SUM(num1, num2);
        diff_mac = DIFF(num1, num2);
        printf("Macro: The sum is %d : The difference is %d\n", sum_mac, diff_mac);

        /* Save the untouched originals to our dynamic array */
        pairs_array = saveArray(pairs_array, &total_numbers, num1, num2);
    }

    /* Print the final array after the user stops inputting numbers */
    printf("\n==================================\n");
    printf("Saved Pairs Array:\n");
    if (total_numbers == 0) {
        printf("No pairs were entered.\n");
    } else {
        /* We increment by PAIR_SIZE to jump to the start of the next pair */
        for (i = 0; i < total_numbers; i += PAIR_SIZE) {
            printf("[%d, %d] ", pairs_array[i], pairs_array[i+1]);
        }
        printf("\n");
    }
    printf("==================================\n");

    /* ALWAYS free dynamically allocated memory to prevent memory leaks! */
    free(pairs_array);

    return 0;
}

/* =========================================================================
 * FUNCTION: findDifferenceAndSum
 * Purpose: Modifies the values at the provided memory addresses.
 * ========================================================================= */
void findDifferenceAndSum(int num1, int num2, int *diff_ptr, int *sum_ptr) {
    /* Dereference the pointers to store the math results. */
    *sum_ptr = num1 + num2;
    *diff_ptr = (num1 > num2) ? (num1 - num2) : (num2 - num1);
}

/* =========================================================================
 * FUNCTION: saveArray
 * Purpose: Uses realloc to dynamically grow the array.
 * ========================================================================= */
int* saveArray(int *arr, int *size, int num1, int num2) {
    int *temp_arr;
    int new_size = *size + PAIR_SIZE; /* Grow by PAIR_SIZE instead of a magic number */

    /* realloc resizes the memory block. */
    temp_arr = (int *)realloc(arr, new_size * sizeof(int));

    if (temp_arr == NULL) {
        printf("Fatal Error: Memory allocation failed!\n");
        free(arr); /* Free existing memory before crashing to be clean */
        exit(1);
    }

    /* Assign the safely allocated memory back to our array pointer */
    arr = temp_arr;

    /* Store the new values at the end of the newly sized array */
    arr[*size] = num1;
    arr[*size + 1] = num2;

    /* Update the size variable back in the main function using the pointer */
    *size = new_size;

    return arr;
}