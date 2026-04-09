# Makefile for Maman 11 - Question 2

# Define the compiler to use
CC = gcc

# Define the compilation flags.
# -Wall: Show all warnings.
# -ansi: Enforce the C89/C90 standard.
# -pedantic: Strictly reject non-standard C extensions.
CFLAGS = -Wall -ansi -pedantic

# The name of the final executable file.
TARGET = turn_on

# The 'all' target is the default. If you just type 'make' in the terminal, it runs this.
all: $(TARGET)

# The rule to build the actual program.
# It tells make: "To build $(TARGET), you need $(TARGET).c"
$(TARGET): $(TARGET).c
	# The actual compile command.
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET)

# A cleanup rule. Running 'make clean' will delete the compiled executable,
# which is useful if you want to force a completely fresh rebuild.
clean:
	rm -f $(TARGET)