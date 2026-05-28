# Compiler and flags as required by the Open University
CC = gcc
CFLAGS = -Wall -ansi -pedantic

# The final executable name
TARGET = mycomp

# All object files required to build the target
OBJS = mycomp.o complex.o

# The main build rule (links the object files and the math library)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

# Compile the main file
mycomp.o: mycomp.c complex.h mycomp.h
	$(CC) -c $(CFLAGS) mycomp.c -o mycomp.o

# Compile the math engine
complex.o: complex.c complex.h
	$(CC) -c $(CFLAGS) complex.c -o complex.o

# Clean rule to easily remove compiled artifacts
clean:
	rm -f *.o $(TARGET)