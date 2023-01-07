# Define a specific compiler to use
CC = gcc 
# Define which compiler flags to use.
CPPFLAGS = -g -Wall -ansi -pedantic 

# Header files located in current directory
INC_DIR = ./
CPPFLAGS += -I$(INC_DIR) # This line adds the value of INC_DIR to CPPFLAGS.

# All '.c' files in current directory
SRCS = $(wildcard *.c)
# Object files created from '.c' files
OBJS = $(SRCS:.c=.o)

# Executable created from object files
TARGET = myset 

# Default target is to build TARGET
all: $(TARGET)
# TARGET depends on object files
$(TARGET): $(OBJS)

# Include dependencies listed in 'depends' file
include depends

depends:
	# Generate dependencies for each source file
	$(CC) -MM -I$(INC_DIR) $(OBJS:.o=.c) > depends


clean:
	# Remove object files, executable, and dependencies files
	-rm -f *.o 
	-rm -f myset 
	-rm -f depends 


run: all
	# Run executable
	./myset

gdb: all
	# Run excutable under gdb debugger
	gdb ./myset


