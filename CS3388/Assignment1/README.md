# Arsalaan Ali

## CS3388 Assignment 1

### Setup

Used Visual Studio 2022 to setup c++ project and glfw

### Creating Window

Used template given (first.cpp) and added the code for a window `glfwCreateWindow(1280, 1000, "Hello World", NULL, NULL);`

### Setting Colour

Used the glColor function to set the color to a desired RGB value `glColor3f(0.0f, 1.0f, 1.0f);`

### Drawing Triangle

Used `glBegin(GL_TRIANGLES)` to start triangle drawing section
Then used `glVertex2f(x, y)` to draw 3 vertexes that could be connected to form a triangle.
Then used `glEnd()` to end triangle drawing section
