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
#include "Plane.hpp"
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

	glm::mat4 M1(1.0f);
	glm::mat4 M2(1.0f);
	glm::mat4 M3(1.0f);
	glm::mat4 MFloor(1.0f);
	glm::mat4 M(1.0f);
	M1 = glm::translate(M2, glm::vec3(-3.0f, 0.0f, 0.0f));
	M3 = glm::translate(M2, glm::vec3(3.0f, 0.0f, 0.0f));
	MFloor = glm::translate(MFloor, glm::vec3(0.f, -1.1f, 0.f));

	Sphere sphere;
	sphere.setUpAxis(2);
	Sphere sphere2;
	Sphere sphere3;
	sphere2.setUpAxis(2);
	sphere3.setUpAxis(2);

	Axes axes(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f));
	Axes worldaxes(glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(10.0f, 10.0f, 10.0f));
	Sphere player;
	player.setUpAxis(2);

	Plane floor(10.0f, "wood.bmp");


	glm::vec3 lightpos(5.0f, 5.0f, 5.0f);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	glm::vec4 color1(0.f, 0.8f, 0.8f, 1.0f);
	glm::vec4 color2(0.f, 0.8f, 0.8f, 1.0f);
	glm::vec4 color3(0.f, 0.8f, 0.8f, 1.0f);
	glm::vec4 color4(0.f, 0.8f, 0.3f, 1.0f);
	float alpha1 = 2;
	float alpha2 = 16;
	float alpha3 = 64;

	do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// cameraControlsGlobe(V, 10);
		// cameraFirstPerson(V, 10);
		cameraThirdPerson(M, V);

		// sphere.draw(lightpos, M1, V, Projection, color1, alpha1);
		// sphere.draw(lightpos, M2, V, Projection, color2, alpha2);
		// sphere.draw(lightpos, M3, V, Projection, color3, alpha3);


	    // M = glm::mat4(1.0f);
	    // M = glm::rotate(M, glm::radians(30.0f), up);
		player.draw(lightpos, M, V, Projection, color4, alpha3);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glm::mat4 tmp = V*M;
		glLoadMatrixf(&tmp[0][0]);
		axes.draw();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();


		worldaxes.draw();

		floor.draw(lightpos, MFloor, V, Projection, color3, alpha1);

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(V));

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

