public class Edge {//edge class
    private Node first, second;//private variables to hold the two nodes connected by this edge
    private String type;//private variable to hold the type of this edge

    public Edge(Node u, Node v, String type) {//constructor
        first = u;
        second = v;
        this.type = type;//use parameters to set the field variables
    }

    public Node firstNode() {//field variable getters
        return first;
    }

    public Node secondNode() {
        return second;
    }

    public String getType() {
        return type;
    }
    
}
