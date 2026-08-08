#ifndef PREPROC_H
#define PREPROC_H

#include "globals.h"

/**
 * This function executes the First Phase of the compilation pipeline (Pre-Processing).
 * Opens the raw source file (.as), identifies macro definitions, saves them
 * into a dynamically linked macro table, and expands those macros into a
 * new intermediate file (.am).
 *
 * If any syntax errors are found, the errors are printed to stdout, and the flawed
 * .am file is deleted to prevent the assembler from continuing with bad data.
 *
 * @param filename The full name of the source file including the ".as" extension.
 * @return TRUE (1) if macro expansion was fully successful, FALSE (0) if any errors occurred.
 */
int expand_macros(const char *filename);

#endif /* PREPROC_H */