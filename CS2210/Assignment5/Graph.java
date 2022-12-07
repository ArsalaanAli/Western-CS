import java.util.Iterator;//importing iterator and arraylist to return iterators
import java.util.ArrayList;

public class Graph{
    private Node[] nodes;//private field variables to hold the nodes and the graph with the edges
    private Edge[][] graph;

    public Graph(int n) {//constructor
        nodes = new Node[n];
        graph = new Edge[n][n];
        for (int i = 0; i < n; i++) {
            nodes[i] = new Node(i);//initialize all the nodes from 0 - n-1
        }
    }

    public Node getNode(int id) throws GraphException {//node getter, throws exception if node does not exist
        if (id < 0 || id >= nodes.length) {
            throw new GraphException("Node does not exist");
        }
        return nodes[id];
    }

    public void addEdge(Node u, Node v, String edgeType) throws GraphException {//function adds an edge to the graph between two nodes
        if (u.getId() < 0 || v.getId() < 0 || u.getId() >= nodes.length || v.getId() >= nodes.length) {
            throw new GraphException("This node does not exist");
        }
        if (graph[u.getId()][v.getId()] != null || graph[v.getId()][u.getId()] != null) {
            throw new GraphException("This edge already exists");//throws exceptions if node doesnt exist or edge already exists
        }
        Edge newEdge = new Edge(u, v, edgeType);//initilizing two edges going both ways between the two nodes
        Edge newEdge2 = new Edge(v, u, edgeType);
        graph[u.getId()][v.getId()] = newEdge;
        graph[v.getId()][u.getId()] = newEdge2;//adding both edges to the graph
    }
    
    public Iterator incidentEdges(Node u) throws GraphException {//returns all the edges adjadcent to a node
        if (u.getId() < 0 || u.getId() >= nodes.length) {
            throw new GraphException("This node does not exist");//throws exception if node does not exist
        }
        ArrayList<Edge> iteratorList = new ArrayList<Edge>();//arraylist to hold all the adjacent edges
        for (Edge e : graph[u.getId()]) {
            if(e != null){
                iteratorList.add(e);//adding every adjacent edge to the arraylist
            }
        }
        return iteratorList.iterator();//returning an iterator containing all the adjacent edges
    }

    public Edge getEdge(Node u, Node v) throws GraphException {//returns the edge between two nodes
        if (u.getId() < 0 || v.getId() < 0 || u.getId() >= nodes.length || v.getId() >= nodes.length) {
            throw new GraphException("This node does not exist");
        }
        if (graph[u.getId()][v.getId()] == null) {
            throw new GraphException("This edge does not exist");//throws exception if either node does not exist or if there is no edge between the two nodes
        }
        return graph[u.getId()][v.getId()];//returns the edge from node v to node u
    }

    public boolean areAdjacent(Node u, Node v) throws GraphException{//returns whether two nodes are adjacent
        if (u.getId() < 0 || v.getId() < 0 || u.getId() >= nodes.length || v.getId() >= nodes.length) {
            throw new GraphException("This node does not exist");////throws exception if either node does not exist
        }
        return graph[u.getId()][v.getId()] != null;//returns whether there is an edge between the two nodes in the graph
    }
}