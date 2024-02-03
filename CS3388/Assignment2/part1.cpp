#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

void drawDog(vector<vector<float>> dog, float xOffset, float yOffset, float rotation) {

    glTranslatef(xOffset + 30.0, yOffset + 30.0, 0.0f); // Translate to the dog's position
    glRotatef(rotation, 0.0f, 0.0f, 1.0f); // Rotate the individual dog
    glBegin(GL_LINE_STRIP);
    for (vector<float> coord : dog) {
        glVertex2f(coord[0] , coord[1]);
    }
    glEnd();


}

int main(void){

    cout << "HELLO" << endl;

    std::ifstream inputFile("dog.txt");

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Read individual tokens from the file
    string xToken, yToken;
    
    vector<vector<float>> dog;

    while (inputFile >> xToken >> yToken) {
        dog.push_back({ stof(xToken), stof(yToken) });
    }

    // Close the file
    inputFile.close();

    double pi = 2 * acos(0.0);

    int rotDegrees = 0;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 1000, "Draw Dog", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 60, 0, 60, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0.0f, 0.0f, 0.0f);

        for (int i = 0; i < 8; i++) {
            float angle = (float) (i) * (2.0f * pi / 8); //calculate the position of the dog around a circle of radius
            float x = 25 * cos(angle);
            float y = 25 * sin(angle);

            drawDog(dog, x, y, rotDegrees);
            
            glLoadIdentity();

        }

        rotDegrees = (rotDegrees + 1) % 360;


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

