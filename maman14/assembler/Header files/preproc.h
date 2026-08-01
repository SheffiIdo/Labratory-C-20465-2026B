#ifndef PREPROC_H
#define PREPROC_H

#include "../Header files/globals.h"

/* =========================================================================
 * CORE PRE-PROCESSING INTERFACE
 * ========================================================================= */

/*
 * Processes a raw input file (.as), expands all contained macros, and
 * outputs a clean intermediate file (.am).
 *
 * Returns 1 (True) on complete success.
 * Returns 0 (False) if any syntactic or file errors occurred (and deletes the .am file).
 */
int expand_macros(const char *base_filename);

#endif