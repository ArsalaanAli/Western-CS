# Arsalaan Ali

## CS3388 Assignment 5

### Project Stucture

- The main project is run using the Makefile in the root folder
- The bonus challenge (rendering the marching in realtime) is run using the Makfile in the bonus folder

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

### The Marching

- In MarchingCubes.hpp
- We do a cubic loop through from (min, min, min) to (max, max, max)
- At each point we check each of the 8 corner cases but running the fuction on that corner, if any of them are inside based on the isovalue we keep track of that corner using a bitwise or

```
int curCase = 0;
for (int i = 0; i < cases.size(); i++){
    if(cases[i]){
        curCase |= bitValues[i];
    }
}
```

- We then use the lookup table to add the proper vertices to the vector

### Processing Normals

- In CalcNormals.hpp
- We get the difference of v2-v1 and v3-v1, which gives us the 2 edges we need

```
std::vector<float> edge1 = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
std::vector<float> edge2 = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};
```

- We then calculate the cross product of these 2 edges to get the normal

```
std::vector<float> normal = crossProduct(edge1, edge2);
```

- Then we normalize the normal, and add the x, y, and z of the normal to the normals vector

### Writing to PLY

- We write the headers and all of the vertex and normals to the ply
- Then we write each of the faces to the ply, making sure that we dont repeat faces so that they are all distinct

### Rendering

- In main.cpp
- We draw the axes, and the bounding cube using `glBegin(GL_LINES);`
- Then we store all of the normals and vertices in a VBO and use glDrawArrays to draw the vertices and normals using the shaders
- The shaders use uniform variables for the Matrix View Projection and LightPosition, which are defined in main.cpp
- The vertex shader defines the position for each vertex, and outputs the postion, normal, camera direction, and lighting direction to the fragment shader
- The fragment shader uses these to calculate the lighting and to combine ambient, diffuse, and specular colors

### Bonus

- Works the same as the base assignment, just a few tweaks to make it run in realtime
- We pass in a reference to the vertices array, as well the x, y, and z coordinates for the current position
- We keep track of how many vertices have been added to the array and return that value, so that we know how many normals to compute for
- In bonus.cpp, we do the cubic looping here instead of doing it in the marching_cubes function. That way we can render inbetween each loop.

```
x += STEPSIZE;
if(x>=MAXSIZE){
    x = MINSIZE;
    y += STEPSIZE;
    if(y>=MAXSIZE){
        y = MINSIZE;
        z += STEPSIZE;
        if(z>=MAXSIZE){
            marching_done = true;
            cout << "done marching" << endl;
            writePLY(vertices, normals, fileName);

        }
    }
}
```

- We write to PLY when the marching is done
- In order to render between each march, we need to bind the bufferdata to the new set of vertices at each step

```
glBindBuffer(GL_ARRAY_BUFFER, vboID);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

// Bind the normal VBO and update data
glBindBuffer(GL_ARRAY_BUFFER, vboNormalID);
glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
```
