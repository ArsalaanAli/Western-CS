# Arsalaan Ali

## CS3388 Assignment 6

### Project Stucture

- The main project is run using the Makefile in the root folder, then running `./main`

### Code Doesn't run

- I was unable to solve an error that i repeatedly get when i try to compile my shaders
  `error: Tessellation control shader outputs can only be indexed by gl_InvocationID`
- I decided to submit anyways as to not lose anymore late marks

### Camera

- Camera contols code is in CamControls.hpp, at each frame the proper camera angle is calculated using:

```
float newX = r * cos(azimunth) * sin(zenith);
float newY = r * cos(zenith);
float newZ = r * sin(azimunth) * sin(zenith);
```

- The mouse position is calculated in refernce to the first click to simulate a "click and drag"

```
glfwGetCursorPos(window, &xpos, &ypos);
dx += xpos - mouseDownX;
dy -= ypos - mouseDownY;

mouseDownX = xpos;
mouseDownY = ypos;
```

- The variable `double r` is used to control the distance from the center to the camera
- If the user presses the up key, the camera will zoom in
- If the user presses the down key, the camera will zoom out

### TessellatedPlane Class

- This class gerates the vertices of the plane that we will be applying the tessellation too
- It stores the vertices, normals, and indices so that we can draw using GL_PATCHES

### The Shaders

- I implement the vertex, tessellation, geometry, and fragment shaders
- The geometry shader has the function `vec3 Gerstner`
- This function is used to calculate the gerstner waves
- I then apply the gerstner waves to the worldspace vectors, and then calculate the normal using the positions of the vertices
- The fragment shader uses a phong like shader to calculate lighting and colours
