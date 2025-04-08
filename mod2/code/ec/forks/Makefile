# Makefile for compiling C programs in current directory

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = 

# Get all .c files in current directory
SRCS = $(wildcard *.c)
# Generate executable names by replacing .c with no extension
EXES = $(SRCS:.c=)

# Default target
all: $(EXES)

# Pattern rule to compile .c files to executables
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Clean target
clean:
	rm -f $(EXES)

.PHONY: all clean