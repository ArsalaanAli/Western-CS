import java.util.Iterator;
import java.util.ArrayList;
import java.util.Arrays;

public class Graph{
    private Node[] nodes;
    private Edge[][] graph;

    public Graph(int n) {
        nodes = new Node[n];
        graph = new Edge[n][n];
        for (int i = 0; i < n; i++) {
            nodes[i] = new Node(i);
        }
    }

    public Node getNode(int id) throws GraphException {
        if (id < 0 || id >= nodes.length) {
            throw new GraphException("Node does not exist");
        }
        return nodes[id];
    }

    public void addEdge(Node u, Node v, String edgeType) throws GraphException {
        if (u.getId() < 0 || v.getId() < 0 || u.getId() >= nodes.length || v.getId() >= nodes.length) {
            throw new GraphException("This node does not exist");
        }
        if (graph[u.getId()][v.getId()] != null || graph[v.getId()][u.getId()] != null) {
            throw new GraphException("This edge already exists");
        }
        Edge newEdge = new Edge(u, v, edgeType);
        Edge newEdge2 = new Edge(v, u, edgeType);
        graph[u.getId()][v.getId()] = newEdge;
        graph[v.getId()][u.getId()] = newEdge2;
    }
    
    public Iterator incidentEdges(Node u) throws GraphException {
        if (u.getId() < 0 || u.getId() >= nodes.length) {
            throw new GraphException("This node does not exist");
        }
        ArrayList<Edge> iteratorList = new ArrayList<Edge>();
        for (Edge e : graph[u.getId()]) {
            if(e != null){
                iteratorList.add(e);
            }
        }
        return iteratorList.iterator();
    }

    public Edge getEdge(Node u, Node v) throws GraphException {
        if (u.getId() < 0 || v.getId() < 0 || u.getId() >= nodes.length || v.getId() >= nodes.length) {
            throw new GraphException("This node does not exist");
        }
        if (graph[u.getId()][v.getId()] == null) {
            throw new GraphException("This edge does not exist");
        }
        return graph[u.getId()][v.getId()];
    }

    public boolean areAdjacent(Node u, Node v) throws GraphException{
        if (u.getId() < 0 || v.getId() < 0 || u.getId() >= nodes.length || v.getId() >= nodes.length) {
            throw new GraphException("This node does not exist");
        }
        return graph[u.getId()][v.getId()] != null;
    }
}