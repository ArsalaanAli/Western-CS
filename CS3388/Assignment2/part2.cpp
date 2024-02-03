#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

static inline double frand() {
    double x = ((double)rand()) / (double)RAND_MAX;
    if (rand() % 2) {
        x *= -1.0;
    }
    return x;
}

int randomCorner() {
    // Generate a random integer between 0 and 2 (inclusive)
    int randomValue = rand() % 3;

    // Map the range 0-2 to -1 to 1
    return randomValue - 1;
}

int main(int argc, char* argv[]){

    GLFWwindow* window;

    int n = stoi(argv[1]);
    int screenWidth = stoi(argv[2]);
    int screenHeight = stoi(argv[3]);
    int curCorner = 0;

    vector<vector<float>> corners = { {1, 1}, { 1, -1}, {-1, -1}, {-1, 1 } };
    vector<float> prevPoint;



    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenHeight, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.1, 1.1, -1.1, 1.1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    // Drawing code outside the loop
    glColor3f(0.0f, 0.0f, 0.0f);
    
    glPointSize(2.0f);

    prevPoint = { (float) frand(), (float) frand() };

    glBegin(GL_POINTS);


    for (int i = 0; i < n; i++) {

        curCorner = ((curCorner + randomCorner()) + 4) % 4;

        vector<float> pi = { (prevPoint[0] + corners[curCorner][0]) / 2.0f, (prevPoint[1] + corners[curCorner][1]) / 2.0f };

        prevPoint = pi;

        glVertex2f(pi[0], pi[1]);
    }


    glEnd();

    
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

