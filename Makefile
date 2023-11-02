# Makefile for MyProject

# Variable for the C compiler being used
CC = gcc

# Variable for compiler flags
CFLAGS = -Wall -Wextra -g

# Source files (.c files)
CFILES = ./src/my_malloc_manager.c ./src/first_fit.c ./src/print_bitmap.c

# Header files (.h files)
HFILES = ./src/my_malloc_manager.h

# Object files (.o files)
OBJFILES = $(CFILES:.c=.o)

# Output executable name
OUT = malloc_manager

# Main target
$(OUT): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJFILES)

# Rule for generating object files
%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c $< -o $@

# Phony target to remove all build files
.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)

# end of Makefile

