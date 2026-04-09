#include <stdio.h>

/* Function prototypes */
long turn_on(long num);
void print_binary(long num);

int main() {
    long original_num, modified_num;

    /* Request user input */
    printf("Please enter an integer number:\n");
    
    /* Read the input. %ld is the format for a long integer */
    if (scanf("%ld", &original_num) == 1) {
        
        /* Apply the bitwise operation */
        modified_num = turn_on(original_num);

        /* Print the "Before" state */
        printf("\nOriginal number in Base 10: %ld\n", original_num);
        printf("Original number in Base 2:  ");
        print_binary(original_num);
        printf("\n");

        /* Check if the value actually changed to determine our output message */
        if (original_num != modified_num) {
            printf("After turning on the 17th bit from the right: A change occurred\n");
        } else {
            printf("The 17th bit from the right was already on, therefore no change\n");
        }

        /* Print the "After" state */
        printf("Modified number in Base 10: %ld\n", modified_num);
        printf("Modified number in Base 2:  ");
        print_binary(modified_num);
        printf("\n");

    } else {
        printf("Invalid input.\n");
    }

    return 0;
}

/*
 * FUNCTION: turn_on
 * PURPOSE: Turns on the 17th bit from the right without altering other bits.
 */
long turn_on(long num) {
    /* * In C, bits are zero-indexed from right to left. 
     * This means the 1st bit is index 0, so the 17th bit is index 16.
     * * '1L' represents the number 1 explicitly as a long integer.
     * '<< 16' shifts that single '1' sixteen places to the left.
     * Our mask now looks like this in binary: 000...00010000000000000000
     */
    long mask = 1L << 16;
    
    /* * Bitwise OR (|) compares bits one by one.
     * 0 | 0 = 0
     * 1 | 0 = 1
     * 0 | 1 = 1
     * 1 | 1 = 1
     * * By OR-ing our number with the mask, all original bits remain exactly 
     * as they were (since they are OR-ed with 0), EXCEPT the 17th bit, 
     * which is forced to become 1.
     */
    return num | mask;
}

/* =========================================================================
 * FUNCTION: print_binary
 * PURPOSE: Prints a long integer in binary (Base 2) format.
 * ========================================================================= */
void print_binary(long num) {
    /* * Determine exactly how many bits make up a 'long' on this specific machine.
     * sizeof(long) gives the number of bytes. Multiply by 8 to get bits.
     * (Usually 64 bits on modern 64-bit systems).
     */
    int num_bits = sizeof(long) * 8;
    int i;
    
    /* * We want to print from left to right (Most Significant Bit down to Least).
     * So we loop backwards from the highest index (63) down to 0.
     */
    for (i = num_bits - 1; i >= 0; i--) {
        
        /* Create a temporary mask with a '1' at the current bit index 'i' */
        long mask = 1L << i;
        
        /* * Bitwise AND (&) checks if both bits are 1.
         * If the bit in our number at index 'i' is a 1, (num & mask) yields a non-zero value (True).
         * If the bit in our number is a 0, (num & mask) yields 0 (False).
         */
        if (num & mask) {
            putchar('1');
        } else {
            putchar('0');
        }
    }
}