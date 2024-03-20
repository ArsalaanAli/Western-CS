// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;


// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;

#include "CamControls.hpp"
#include "MarchingCubes.hpp"
#include "CalcNormals.hpp"
#include "Shader.hpp"
#include "WritePly.hpp"

#include <vector>
#include <iostream>


class Axes {

	glm::vec3 origin;
	glm::vec3 extents;

	glm::vec3 xcol = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 ycol = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 zcol = glm::vec3(0.0f, 0.0f, 1.0f);

public:

	Axes(glm::vec3 orig, glm::vec3 ex) : origin(orig), extents(ex) {}

	void draw() {

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();


		glLineWidth(2.0f);
		glBegin(GL_LINES);
		glColor3f(xcol.x, xcol.y, xcol.z);
		glVertex3f(origin.x, origin.y, origin.z);
		glVertex3f(origin.x + extents.x, origin.y, origin.z);

		glVertex3f(origin.x + extents.x, origin.y, origin.z);
		glVertex3f(origin.x + extents.x, origin.y, origin.z+0.1);
		glVertex3f(origin.x + extents.x, origin.y, origin.z);
		glVertex3f(origin.x + extents.x, origin.y, origin.z-0.1);

		glColor3f(ycol.x, ycol.y, ycol.z);
		glVertex3f(origin.x, origin.y, origin.z);
		glVertex3f(origin.x, origin.y + extents.y, origin.z);

		glVertex3f(origin.x, origin.y + extents.y, origin.z);
		glVertex3f(origin.x, origin.y + extents.y, origin.z+0.1);
		glVertex3f(origin.x, origin.y + extents.y, origin.z);
		glVertex3f(origin.x, origin.y + extents.y, origin.z-0.1);
		
		glColor3f(zcol.x, zcol.y, zcol.z);
		glVertex3f(origin.x, origin.y, origin.z);
		glVertex3f(origin.x, origin.y, origin.z + extents.z);
		
		glVertex3f(origin.x, origin.y, origin.z + extents.z);
		glVertex3f(origin.x+0.1, origin.y, origin.z + extents.z);

		glVertex3f(origin.x, origin.y, origin.z + extents.z);
		glVertex3f(origin.x-0.1, origin.y, origin.z + extents.z);
		glEnd();


		glPopMatrix();
	}

};

class BoundingCube {

	int min;
	int max;

public:

	BoundingCube(int min, int max) : min(min), max(max) {}

	void draw() {

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();


		glLineWidth(2.0f);
		glBegin(GL_LINES);

		glColor3f(1.0f, 1.0f, 1.0f);
		  // Draw bottom square
        glVertex3f(min, min, min);
        glVertex3f(max, min, min);

        glVertex3f(max, min, min);
        glVertex3f(max, min, max);

        glVertex3f(max, min, max);
        glVertex3f(min, min, max);

        glVertex3f(min, min, max);
        glVertex3f(min, min, min);

        // Draw top square
        glVertex3f(min, max, min);
        glVertex3f(max, max, min);

        glVertex3f(max, max, min);
        glVertex3f(max, max, max);

        glVertex3f(max, max, max);
        glVertex3f(min, max, max);

        glVertex3f(min, max, max);
        glVertex3f(min, max, min);

        // Connect top and bottom squares
        glVertex3f(min, min, min);
        glVertex3f(min, max, min);

        glVertex3f(max, min, min);
        glVertex3f(max, max, min);

        glVertex3f(max, min, max);
        glVertex3f(max, max, max);

        glVertex3f(min, min, max);
        glVertex3f(min, max, max);

		glEnd();


		glPopMatrix();
	}

};


float model(float x, float y, float z){
	float res = y - sin(x) * cos(z);
	return res;
}

//////////////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[])
{
    const float MINSIZE = -5;
    const float MAXSIZE = 5;
    const float STEPSIZE = 0.05f;
	const string fileName = "example1.ply";

	vector<float> vertices = marching_cubes(&model, 0, MINSIZE, MAXSIZE, STEPSIZE);
    vector<float> normals = compute_normals(vertices);

	writePLY(vertices, normals, fileName);

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	float screenW = 1400;
	float screenH = 900;
	window = glfwCreateWindow( screenW, screenH, "An Example", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}


	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.3f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint ProgramID = LoadShaders("Marching.vertexshader", "Marching.fragmentshader");
	GLuint MVPID;
    GLuint MID;
    GLuint VID;
    GLuint LightPosID;
    GLuint colorID;
    GLuint alphaID;

	MID = glGetUniformLocation(ProgramID, "M");
	VID = glGetUniformLocation(ProgramID, "V");
	LightPosID = glGetUniformLocation(ProgramID, "LightPosition_worldspace");
	colorID = glGetUniformLocation(ProgramID, "modelcolor");
	alphaID = glGetUniformLocation(ProgramID, "alpha");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(ProgramID, "MVP");
	glm::mat4 MVP;

	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), &vertices[0], GL_STATIC_DRAW);
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*) 0           // buffer offset
	);

    GLuint vboNormalID; // Add a new VBO for normals

    // Inside the main function
    glGenBuffers(1, &vboNormalID);
    glBindBuffer(GL_ARRAY_BUFFER, vboNormalID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);

    // Inside the drawing loop
    glBindBuffer(GL_ARRAY_BUFFER, vboNormalID);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // Set attribute pointer for normals
    glEnableVertexAttribArray(1);

	Axes ax(glm::vec3(MINSIZE, MINSIZE, MINSIZE), glm::vec3(MAXSIZE-MINSIZE, MAXSIZE-MINSIZE, MAXSIZE-MINSIZE));
    BoundingCube bc(MINSIZE, MAXSIZE);

    glm::vec3 eye = {5.0f, 5.0f, 5.0f};
    glm::vec3 up = {0.0f, 1.0f, 0.0f};
    glm::vec3 center = {0.0f, 0.0f, 0.0f};

    glm::mat4 M = glm::mat4(1.0f);
    
    glm::mat4 V = glm::lookAt(eye, center, up); 
	glm::vec3 lightpos(5.0f, 5.0f, 5.0f);
	glm::vec4 color(0.f, 0.8f, 0.8f, 1.0f);
	float alpha = 64;



    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), screenW/screenH, 0.001f, 1000.0f);
		// Projection = glm::mat4(1.0f);

	do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		
		glLoadMatrixf(glm::value_ptr(Projection));

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
		ax.draw();



        SphericalCamera(V);

		glLoadMatrixf(glm::value_ptr(V));

		MVP = Projection * V * M;


		glUseProgram(ProgramID);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(MID, 1, GL_FALSE, &M[0][0]); //model matrix always identity.
	    glUniformMatrix4fv(VID, 1, GL_FALSE, &V[0][0]);
		glUniform3f(LightPosID, lightpos.x, lightpos.y, lightpos.z);
		glUniform4fv(colorID, 1, &color[0]);
		glUniform1f(alphaID, alpha);

		glBindVertexArray(vaoID);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glBindVertexArray(0);

		glUseProgram(0);
		glBindTexture(GL_TEXTURE_2D, 0);

        bc.draw();

        // Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();


		// // Bind the VBO and update data
		// glBindBuffer(GL_ARRAY_BUFFER, vboID);
		// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		// // Bind the normal VBO and update data
		// glBindBuffer(GL_ARRAY_BUFFER, vboNormalID);
		// glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);


	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup shader
	glDeleteProgram(ProgramID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}


