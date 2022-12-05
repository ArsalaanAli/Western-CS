public class Graph implements GraphADT {
    private Node[] nodes;
    private Edge[][] graph;

    public Graph(int n) {
        nodes = new Node[n];
        graph = new Edge[n][n];
        for (int i = 0; i < n; i++) {
            nodes[i] = new Node(i);
        }
    }
    
}