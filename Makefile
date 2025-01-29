# Compiler
CC = gcc

# Compiler flags
CFLAGS = -lncursesw -lSDL2 -lSDL2_mixer

# Target executable
TARGET = program

# Source files
SRC = main.c menu.c connect.c music.c scoreboard.c monster.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target (build the executable)
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lncursesw -lSDL2 -lSDL2_mixer

# Rule to compile each .c file into a .o object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files (object files, the executable)
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets (these aren't files, so make won't get confused)
.PHONY: all clean

