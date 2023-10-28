# Makefile for MyProject

# Variable for the C compiler being used
CC = gcc

# Variable for compiler flags
CFLAGS = -Wall -Wextra -g

# Source files (.c files)
CFILES = my_malloc_manager.c

# Header files (.h files)
HFILES = my_malloc_manager.h

# Object files (.o files)
OBJFILES = $(CFILES:.c=.o)

# Output executable name
OUT = MyProject

# Main target
$(OUT): $(OBJFILES)
    # Compiling and linking all object files into an executable
    $(CC) $(CFLAGS) -o $(OUT) $(OBJFILES)

# Rule for generating object files
%.o: %.c $(HFILES)
    # Compiling source files into object files
    $(CC) $(CFLAGS) -c $< -o $@

# Phony target to remove all build files
.PHONY: clean
clean:
    # Removing object files and the executable
    rm -f $(OBJFILES) $(OUT)

# end of Makefile

