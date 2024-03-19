#ifndef _CAM_CONTROLS_H_
#define _CAM_CONTROLS_H_

#include <glm/glm.hpp>
#include "math.h"

static const double _PI = 2.0*asin(1);
const double speed = 0.5;


void cameraThirdPerson(glm::mat4& M, glm::mat4& V) {}

void cameraFirstPerson(glm::mat4& V, float start) {
    glm::vec3 center = {0, 0, 0};
    glm::vec3 position;
    static double azimunth = 1;
    static double zenith = 1;
    static double r = 5;
    static double mouseDownX;
    static double mouseDownY;
    static bool firstPress = true;
    double currentTime = glfwGetTime();
    static double lastTime = glfwGetTime();
    float deltaTime = (currentTime - lastTime);
    lastTime = currentTime;

    float dx = 0.0f, dy = 0.0f;
    float speed = 4.0f;
    
    if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS) {
        double change = deltaTime * speed;
        if(r-change>0){
            r -= change;
        }
    }
    
    // Move backward
    if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS) {
        r += deltaTime * speed;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        cout << "work" << endl;
        if (firstPress){
            glfwGetCursorPos(window, &mouseDownX, &mouseDownY);
            firstPress = false;
        }

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        dx += xpos - mouseDownX;
        dy -= ypos - mouseDownY;

        mouseDownX = xpos;
        mouseDownY = ypos;

        azimunth += dx * deltaTime;
        zenith += dy * deltaTime;    
    }

    if(glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_LEFT ) == GLFW_RELEASE){
        firstPress = true;
    }

    float newX = r * cos(azimunth) * sin(zenith);
    float newY = r * cos(zenith);
    float newZ = r * sin(azimunth) * sin(zenith);
    position = {newX, newY, newZ};

    std::cout << position.x << " " <<  position.y << " " << position.z << std::endl;

    glm::vec3 up = {0.0f, 1.0f, 0.0f};
    V = glm::lookAt(position, center, up);
}



void cameraControlsGlobe(glm::mat4& V, float start) {}

#endif
