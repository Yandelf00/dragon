# Variables
CC = gcc
CFLAGS = -g -Wall -Iinclude   # -Iinclude tells GCC where the .h files are
SRC_DIR = src
OBJ_DIR = obj
TARGET = compiler_exec      # Name of your final program

# Automatically find all .c files in src/
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Convert .c file paths to .o file paths in the obj/ directory
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default rule
all: $(OBJ_DIR) $(TARGET)

# Create the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule for Valgrind
test: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean test
