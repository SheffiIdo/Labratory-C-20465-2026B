#ifndef SEEK_H
#define SEEK_H

/* --- MACROS FOR ARGUMENT PARSING --- */
#define MIN_ARGS 3          /* Program name + n + at least 1 file */
#define ARG_N_INDEX 1       /* Position of the character count 'n' in argv */
#define FIRST_FILE_INDEX 2  /* Starting position of the file list in argv[cite: 1] */

/*
 * HELPER FUNCTION PROTOTYPES
 */
void process_file(const char *filename, long n);

#endif /* SEEK_H */