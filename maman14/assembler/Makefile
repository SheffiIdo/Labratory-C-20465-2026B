# Compiler settings strictly matching the Open University C90 requirements
CC = gcc
CFLAGS = -ansi -Wall -pedantic -g -I"Header files"

# The final executable name
EXEC = assembler

# The list of object files needed to build the program
OBJS = assembler.o preproc.o macro_table.o errors.o utils.o \
       extern_usage.o file_writer.o first_pass.o parser.o \
       second_pass.o symbol_table.o

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

extern_usage.o: Source\ files/extern_usage.c
	$(CC) $(CFLAGS) -c "Source files/extern_usage.c"

file_writer.o: Source\ files/file_writer.c
	$(CC) $(CFLAGS) -c "Source files/file_writer.c"

first_pass.o: Source\ files/first_pass.c
	$(CC) $(CFLAGS) -c "Source files/first_pass.c"

parser.o: Source\ files/parser.c
	$(CC) $(CFLAGS) -c "Source files/parser.c"

second_pass.o: Source\ files/second_pass.c
	$(CC) $(CFLAGS) -c "Source files/second_pass.c"

symbol_table.o: Source\ files/symbol_table.c
	$(CC) $(CFLAGS) -c "Source files/symbol_table.c"

# Clean rule to wipe compiled files before a fresh build or pushing to Git
clean:
	rm -f *.o $(EXEC)