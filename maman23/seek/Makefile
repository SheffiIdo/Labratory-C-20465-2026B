# Compiler and Flags
CC = gcc
CFLAGS = -Wall -ansi -pedantic

# Target Executable Name
TARGET = seek

# Default Rule: Build the executable
all: $(TARGET)

# Link the executable from object files
$(TARGET): seek.o
	$(CC) $(CFLAGS) seek.o -o $(TARGET)

# Compile source files into object files
seek.o: seek.c seek.h
	$(CC) -c $(CFLAGS) seek.c -o seek.o

# Clean Rule: Remove compiled binaries and object files
clean:
	rm -f *.o $(TARGET)