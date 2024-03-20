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
#include "shader.hpp"

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


float wave(float x, float y, float z){
    return y - sin(x) - cos(z);
}

//////////////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[])
{
    const float MINSIZE = -5;
    const float MAXSIZE = 5;
    const float STEPSIZE = 0.1f;

    cout << "marchinga" << endl;
    vector<float> vertices = marching_cubes(&wave, 0, MINSIZE, MAXSIZE, STEPSIZE);
    vector<float> normals = compute_normals(vertices);

    cout << vertices.size() << " SIZES " << normals.size() << endl;

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
	float screenW = 1400;
	float screenH = 900;
	window = glfwCreateWindow( screenW, screenH, "An Example", NULL, NULL);
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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    std::string VertexShaderCode = "\
    	#version 330 core\n\
		layout(location = 0) in vec3 vertexPosition;\n\
		layout(location = 1) in vec3 normalPosition;\n\
		out vec2 normalOut;\n\
		uniform mat4 MVP;\n\
		void main(){ \n\
			gl_Position =  MVP * vec4(vertexPosition,1);\n\
			normalOut = normalPosition;\n\
		}\n";

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode = "\
		#version 330 core\n\
		in vec3 normalOut; \n\
        out vec4 fragColor;\n\
		void main() {\n\
			fragColor = vec4(Normal, 1.0);\n\
		}\n";
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Compile Fragment Shader
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);


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

		glBindVertexArray(vaoID);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glBindVertexArray(0);

		glUseProgram(0);
		glBindTexture(GL_TEXTURE_2D, 0);

        bc.draw();

        // Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();


	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup shader
	glDeleteProgram(ProgramID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}


