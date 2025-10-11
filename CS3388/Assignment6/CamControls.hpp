#ifndef _CAM_CONTROLS_H_
#define _CAM_CONTROLS_H_

#include <glm/glm.hpp>
#include "math.h"
#include <iostream>

using namespace std;

static const double _PI = 2.0*asin(1);
const double speed = 0.5;

void SphericalCamera(glm::mat4& V) {
    glm::vec3 center = {0, 0, 0};
    glm::vec3 position;
    static double azimunth = _PI/4;
    static double zenith = _PI/4;
    static double r = 2;
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

    // cout << position.x <<  " " << position.y << " " << position.z << " " << r << endl;

    glm::vec3 up = {0.0f, 1.0f, 0.0f};
    V = glm::lookAt(position, center, up);
}
#endif
