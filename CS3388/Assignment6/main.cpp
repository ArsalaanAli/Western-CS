#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

GLFWwindow *window;

#include "PlaneMesh.hpp" // Include the header file for TessellatedPlane
#include "CamControls.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(800, 600, "Tessellation Example", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    float time = 0.0f;

    // Create TessellatedPlane object
    TessellatedPlane plane(-1.0f, 1.0f, 0.1f);

    // Set up projection and view matrices
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 1.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the framebuffer
        glClear(GL_COLOR_BUFFER_BIT);

        time = glfwGetTime();

        // Calculate MVP matrix
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 MVP = projection * view * model;

		SphericalCamera(view);

		// Draw the tessellated plane
        plane.draw(MVP, view, time);
		

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
