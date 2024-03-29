# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11

# OpenGL and GLFW libraries
LIBS = -lGL -lglfw -lGLEW

# Source files
SRCS = bonus.cpp

# Executable name
EXEC = bonus

# Default target
all: $(EXEC)

# Compile the source files
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC) $(LIBS)

# Clean the build files
clean:
	rm -f $(EXEC)