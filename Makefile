# Define the compiler
CC = gcc

# Define the flags
# -Wall: enables all compiler's warning messages
# -ansi: enforces the C90 (ANSI) standard
# -pedantic: issues warnings for strict ISO C compliance
CFLAGS = -Wall -ansi -pedantic

# The default target that runs when you just type 'make'
all: m11

# Rule to build maman11
# Format -> target: dependencies
m11: maman11/maman11.c
	$(CC) $(CFLAGS) maman11/maman11.c -o m11

# Clean up the folder by removing the executable
clean:
	rm -f m11