// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

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

#include <iostream>
#include <vector>

#include "shader.hpp"
#include "Sphere.hpp"
#include "CamControls.hpp"
#include "LoadBMP.hpp"
#include "Axes.hpp"

//////////////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[])
{

	///////////////////////////////////////////////////////
	float screenW = 1400;
	float screenH = 900;
	float stepsize = 0.1f;

	float xmin = -5;
	float xmax = 5;
	float ymin = -5;
	float ymax = 5;
	float isoval = 0.2;

	if (argc > 1 ) {
		screenW = atoi(argv[1]);
	}
	if (argc > 2) {
		screenH = atoi(argv[2]);
	}
	if (argc > 3) {
		stepsize = atof(argv[3]);
	}

	///////////////////////////////////////////////////////

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( screenW, screenH, "Phong", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
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


	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.3f, 0.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glDisable(GL_CULL_FACE);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	// Projection = glm::mat4(1.0f);
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), screenW/screenH, 0.001f, 1000.0f);
	glLoadMatrixf(glm::value_ptr(Projection));

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glm::vec3 eye = {0.0f, 3.0f, 5.0f};
	// glm::vec3 eye = {-5.0f, 2.0f, -5.0f};
	glm::vec3 up = {0.0f, 1.0f, 0.0f};
	glm::vec3 center = {0.0f, 0.0f, 0.0f};
	//glm::mat4 V;

	glm::mat4 V = glm::lookAt(eye, center, up);
	glLoadMatrixf(glm::value_ptr(V));

	glm::mat4 M2(1.0f);
	Sphere globe(5.0f, 36, 18, true, 2, true);
	Axes worldaxes({0,0,0}, {8,8,8});


	unsigned char* data;
	unsigned int width, height;
	loadBMP("map.bmp", &data, &width, &height);
	// fprintf(stderr, "w: %d, h: %d\n", width, height);

	GLuint globeTexID;
	glGenTextures(1, &globeTexID);
	glBindTexture(GL_TEXTURE_2D, globeTexID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);


	glm::vec3 lightpos(5.0f, 5.0f, 5.0f);
	glm::vec4 color1(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cameraControlsGlobe(V, 10);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, globeTexID);
		globe.draw(lightpos, M2, V, Projection, color1, 0.0f);
		glBindTexture(GL_TEXTURE_2D, 0);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadMatrixf(&V[0][0]);
		worldaxes.draw();
		glPopMatrix();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();


	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

