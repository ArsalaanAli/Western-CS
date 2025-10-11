#ifndef _CAM_CONTROLS_H_
#define _CAM_CONTROLS_H_

#include <glm/glm.hpp>
#include "math.h"

static const double _PI = 2.0*asin(1);


void cameraThirdPerson(glm::mat4& M, glm::mat4& V) {}

void cameraFirstPerson(glm::mat4& V, float start) {
    glm::vec3 eye = {0, 1, 5};

    static GLfloat theta = glm::radians(-90.0f);
    static glm::vec3 position = eye;
    double currentTime = glfwGetTime();
    static double lastTime = glfwGetTime();
    float deltaTime = (currentTime - lastTime);
    lastTime = currentTime;

    float dx = 0.0f, dy = 0.0f;
    float speed = 6.0f;
    // Move forward
    if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS) {
        dy += deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS) {
        dy -= deltaTime * speed;
    }
    // Rotate counterclockwise
    if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS) {
        dx -= deltaTime * speed;
    }
    // rotate clockwise
    if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS) {
        dx += deltaTime * speed;
    }

    theta += dx;
    glm::vec3 dir(cos(theta), 0, sin(theta));

    if (dy != 0.0f) {
        position += dy*dir;
    }

    glm::vec3 up = {0.0f, 1.0f, 0.0f};
    V = glm::lookAt(position, position + dir, up);

    // if (dx != 0.0f || dy != 0.0f) {
    //     std::cerr << "eye pos: " << glm::to_string(position) << std::endl;
    //     std::cerr << "theta  : " << glm::degrees(theta) << std::endl;
    // }
}



void cameraControlsGlobe(glm::mat4& V, float start) {}

#endif
