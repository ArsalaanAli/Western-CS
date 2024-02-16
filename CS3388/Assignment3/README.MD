# Arsalaan Ali

## CS3388 Assignment 3

### Setup

Used Visual Studio 2022 to setup c++ project with glfw

### Creating Nodes

- a Deque data strcuture is used to hold the nodes, this allows us to insert to the front or back of a queue with 0(1) efficiency
- in the main loop we check to see if a user has clicked, if they have we check if they clicked on an existing node, or on an empty space
- if they clicked on an empty space then we create a node with the `void addNode(deque<Node> &nodes, float mx, float my)` function
- The addNode function checks if the current click possition is closer to the front node or the back node, and the new node gets added to that side of the queue, with the old node getting a second control point / handle

### Drawing Nodes and Curves

- Every step for drawing is in its own seperate function
- `renderNodes(nodes);` `renderControlPointLines(nodes);` `renderControlPoints(nodes);`\
  each of these functions draws its respective component
- The Bezier curves are drawn using 2 functions`drawCurve(Node node1, Node node2)` and `BezierCurvePoint(float t, Point p0, Point p1, Point p2, Point p3)`
- the drawCurve() function goes through 200 iterations where it calls the BezierCurvePoint function at each interation to find the ith point on the bezier curve, all of those points are drawn as a line strip using GL_LINE_STRIP

### Moving Nodes

- If a user clicks near an existing node or ctrl point, then that point is moved
- we use the pointer `Point* curPoint` to keep track of the current point being moved when the user clicks on a node
- that node is moved to the mouse position as long as the user holds down left click

### Moving Control Points

- `Point* curPoint;` `Point* curCtrl;` `Point* otherCtrl;` are all used to keep track of the control points being moved
- when a user clicks on a control point, these pointers are set to the control point they clicked on, the node that the control point is connected, and the other control point connected to this node and `bool isCtrlPoint` is set to true
- if `isCtrlPoint` is true, then we move `curCtrl` to be at the same position as the mouse as long as the user is holding left click, we move `otherCtrl` with respect to it as well

### Clearing Canvas

```
if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            nodes.clear();
    }
```

- this code is used to clear the canvas when the user presses 'E'
- we use the .clear() function of the deque data structure to remove all nodes
