#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <deque>
#include <string>

using namespace std;

struct Point {
    float x;
    float y;
};

// Define the Node struct inheriting from Point
struct Node : Point {
    Point handle1;
    Point handle2;
};

Point BezierCurvePoint(float t, Point p0, Point p1, Point p2, Point p3) {
    float mt = 1 - t;
    float mt2 = mt * mt;
    float mt3 = mt2 * mt;
    float t2 = t * t;
    float t3 = t2 * t;

    Point point;
    point.x = mt3 * p0.x + 3 * mt2 * t * p1.x + 3 * mt * t2 * p2.x + t3 * p3.x;
    point.y = mt3 * p0.y + 3 * mt2 * t * p1.y + 3 * mt * t2 * p2.y + t3 * p3.y;

    return point;
}

void drawCurve(Node node1, Node node2) {
    int PolyLine = 200;
    for (int i = 0; i < PolyLine; ++i) {
        double t = static_cast<float>(i) / (PolyLine - 1);
        Point temp = (BezierCurvePoint(t, node1, node1.handle2, node2.handle1, node2));
        glVertex2f(temp.x, temp.y);
    }
}

void addNode(deque<Node> &nodes, float mx, float my) { 
    Node newNode;
    newNode.x = mx;
    newNode.y = my;

    if (nodes.empty()) {
        newNode.handle2.x = newNode.x;
        newNode.handle2.y = newNode.y + 50;
        nodes.push_back(newNode);
        return;
    }

    Node &front = nodes.front();
    Node &back = nodes.back();
    int frontDist = (front.x - mx) * (front.x - mx) + (front.y - my) * (front.x - mx);
    int backDist = (back.x - mx) * (back.x - mx) + (back.y - my) * (back.x - mx);
    if (frontDist <= backDist) {
        //adding to front
        front.handle1.x = front.x + (front.x - front.handle2.x);
        front.handle1.y = front.y + (front.y - front.handle2.y);
        //add handle2
        newNode.handle2.x = newNode.x;
        newNode.handle2.y = newNode.y+50;
        nodes.push_front(newNode);
    }
    else {
        //adding to back

        back.handle2.x = back.x + (back.x - back.handle1.x);
        back.handle2.y = back.y + (back.y - back.handle1.y);
        //add handle1
        newNode.handle1.x = newNode.x;
        newNode.handle1.y = newNode.y + 50;
        nodes.push_back(newNode);
    }
}

void renderNodes(deque<Node>& nodes) {
    //rendering nodes
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < nodes.size(); i++) {
        glVertex2f(nodes[i].x, nodes[i].y);
    }
    glEnd();
}


void renderControlPoints(deque<Node> &nodes) {
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);

    //rendering control points
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < nodes.size(); i++) {
        if (i == 0) {
            glVertex2f(nodes[i].handle2.x, nodes[i].handle2.y);
        }
        else if (i == nodes.size() - 1) {
            glVertex2f(nodes[i].handle1.x, nodes[i].handle1.y);
        }
        else {
            glVertex2f(nodes[i].handle1.x, nodes[i].handle1.y);
            glVertex2f(nodes[i].handle2.x, nodes[i].handle2.y);
        }
    }
    glEnd();

    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_BLEND);
}

void renderControlPointLines(deque<Node> &nodes) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(3, 0xAAAA);

    //rendering dotted lines between control points
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < nodes.size(); i++) {
        if (i == 0) {
            glVertex2f(nodes[i].handle2.x, nodes[i].handle2.y);
            glVertex2f(nodes[i].x, nodes[i].y);
        }
        else if (i == nodes.size() - 1) {
            glVertex2f(nodes[i].handle1.x, nodes[i].handle1.y);
            glVertex2f(nodes[i].x, nodes[i].y);
        }
        else {
            glVertex2f(nodes[i].handle1.x, nodes[i].handle1.y);
            glVertex2f(nodes[i].x, nodes[i].y);
            glVertex2f(nodes[i].handle2.x, nodes[i].handle2.y);
            glVertex2f(nodes[i].x, nodes[i].y);
        }
    }
    glEnd();

    glDisable(GL_LINE_STIPPLE);
}

void renderBezierCurves(deque<Node> &nodes) {
    glLineWidth(2.0f);
    //render bezier curves
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i < nodes.size() - 1; i++) {
        drawCurve(nodes[i], nodes[i + 1]);
    }
    glEnd();
}


int main(int argc, char* argv[]) {

    GLFWwindow* window;
    int screenWidth = stoi(argv[1]);
    int screenHeight = stoi(argv[2]);

    deque<Node> nodes;


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenHeight, "Pen Tool", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glViewport(0, 0, screenWidth, screenHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    Point* curPoint = nullptr;
    Point* curCtrl = nullptr;
    Point* otherCtrl = nullptr;
    bool isCtrlPoint = false;

    int leftButtonPressed = false;

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0.0f, 0.0f, 0.0f);

        glPointSize(10.0f);

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            nodes.clear();
        }


        int leftState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        ypos = screenHeight - ypos;

        if (leftState == GLFW_PRESS && leftButtonPressed) {
            if (curPoint) {

                if (isCtrlPoint) {
                    curCtrl->x = xpos;
                    curCtrl->y = ypos;
                    otherCtrl->x = curPoint->x + (curPoint->x - curCtrl->x);
                    otherCtrl->y = curPoint->y + (curPoint->y - curCtrl->y);
                }
                else {
                    curPoint->x = xpos;
                    curPoint->y = ypos;
                }
            }
        }
        else if (leftState == GLFW_PRESS && !leftButtonPressed) {
            //mouse first press
            leftButtonPressed = true;
            float minDist = 101;
            for (Node &n : nodes) {
                float dist = (xpos - n.x) * (xpos - n.x) + (ypos - n.y) * (ypos - n.y);
                if (dist <= 100 && dist < minDist) {
                    curPoint = &n;
                    minDist = dist;
                }
                dist = (xpos - n.handle1.x) * (xpos - n.handle1.x) + (ypos - n.handle1.y) * (ypos - n.handle1.y);
                if (dist <= 100 && dist < minDist) {
                    curPoint = &n;
                    curCtrl = &n.handle1;
                    otherCtrl = &n.handle2;
                    minDist = dist;
                    isCtrlPoint = true;
                }
                dist = (xpos - n.handle2.x) * (xpos - n.handle2.x) + (ypos - n.handle2.y) * (ypos - n.handle2.y);
                if (dist <= 100 && dist < minDist) {
                    curPoint = &n;
                    curCtrl = &n.handle2;
                    otherCtrl = &n.handle1;
                    minDist = dist;
                    isCtrlPoint = true;
                }
            }
            if (!curPoint) {
                addNode(nodes, (float)xpos, (float)ypos);
            }
        }
        else if (leftState != GLFW_PRESS && leftButtonPressed) {
            //mouse first released
            leftButtonPressed = false;
            curPoint = nullptr;
        }

        if (nodes.size() > 0) {

            renderNodes(nodes);

            renderControlPointLines(nodes);

            renderControlPoints(nodes);

            renderBezierCurves(nodes);
        }


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

