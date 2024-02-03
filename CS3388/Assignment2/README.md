# Arsalaan Ali

## CS3388 Assignment 2

## Part 1

### Setup

Used Visual Studio 2022 to setup c++ project and glfw

### Reading File

Use given file "dog.txt" to read each point as pairs of tokens (x, y)\
Each point is then stored in a 2d vector of floats, with each float vector holding the x and y position of the point

### Viewing Volume

Viewing volume is set with this code\
`glMatrixMode(GL_PROJECTION);`\
`glLoadIdentity();`\
`glOrtho(0, 60, 0, 60, -1, 1);`\
`glMatrixMode(GL_MODELVIEW);`

### Draw Dog Function

The drawDog() function is used to draw a dog to screen using all of the points read in from the dog.txt file\
The function takes in the position and rotation that the dog should be drawn with

### Drawing in a circle

A for loop goes through 8 iterations, on each iteration the coordinates of the angle of a circle of radius 25 are calculated and stored in the x and y variables\
The the draw dog function is called with those variables and the rotationDegrees variable

### Rotation Degrees

Each frame the rotationDegrees int is incremented and modulo 360. This increases the angle of the rotation every frame

## Part 2

### Command Line Arguments

argv is used to grab each of the command line arguments for n, screenWidth, and screenHeight\
Each argument is stored in an integer

### Corner Array

Each of the 4 corners are stored in vector "corners", each corner in this array is 2 positions away from its opposite corner

### Random Corner Function

This function returns an integer between -1 and 1. This is used to grab a corner that is not opposite to the current corner, since the opposite corner is always 2 positions away, if we only move -1, 0, or 1 from the current position, we will always get a non-opposite corner

### Plotting Points

The frand() function is used initally to select a random point where x and y are between -1 and 1, this point is stored in the vector\<float> prevPoint\
A loop then goes through N iterations, and at each iteration we select a non-opposite corner and get the point halfway between prevPoint and the new corner\
We plot this new point, and then we set this point to prevPoint, and the loop continues.

### Outside of loop

The code is drawn outside of the loop, and so the while loop runs to display the code, but nothing is drawn inside it.
