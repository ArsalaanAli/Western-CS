public class Edge {
    private Node first, second;
    private String type;

    public Edge(Node u, Node v, String type) {
        first = u;
        second = v;
        this.type = type;
    }

    public Node firstNode() {
        return first;
    }

    public Node secondNode() {
        return second;
    }

    public String getType() {
        return type;
    }
    
}
