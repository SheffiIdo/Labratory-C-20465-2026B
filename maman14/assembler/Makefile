# Compiler settings strictly matching the Open University C90 requirements
CC = gcc
CFLAGS = -ansi -Wall -pedantic -g -I"Header files"

# The final executable name
EXEC = assembler

# The list of object files needed to build the program
OBJS = assembler.o preproc.o macro_table.o errors.o utils.o

# Default target: builds the main executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Rules for compiling individual object files from the "Source files" directory
assembler.o: Source\ files/assembler.c
	$(CC) $(CFLAGS) -c "Source files/assembler.c"

preproc.o: Source\ files/preproc.c
	$(CC) $(CFLAGS) -c "Source files/preproc.c"

macro_table.o: Source\ files/macro_table.c
	$(CC) $(CFLAGS) -c "Source files/macro_table.c"

errors.o: Source\ files/errors.c
	$(CC) $(CFLAGS) -c "Source files/errors.c"

utils.o: Source\ files/utils.c
	$(CC) $(CFLAGS) -c "Source files/utils.c"

# Clean rule to wipe compiled files before a fresh build or pushing to Git
clean:
	rm -f *.o $(EXEC)