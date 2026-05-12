# ==========================================
# Makefile for Maman 12: difference_and_sum
# ==========================================

CC = gcc
CFLAGS = -Wall -ansi -pedantic

# The target executable name
TARGET = difference_and_sum

# The source file(s)
SRCS = difference_and_sum.c

# The default rule when you type 'make'
all: $(TARGET)

# How to build the target
$(TARGET): $(SRCS) difference_and_sum.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# A rule to clean up the compiled files
clean:
	rm -f $(TARGET)