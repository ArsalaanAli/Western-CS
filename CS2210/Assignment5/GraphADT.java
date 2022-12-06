import java.util.Iterator;

public interface GraphADT {

  public void addEdge(Node nodeu, Node nodev, String edgeType) 
                                              throws GraphException;
                    /* Adds to the graph an edge connecting the given nodes.
                       The type of the edge is as indicated. Throws a GraphException
		       if either node does not exist or if the edge is already 
		       in the graph.*/

  public Node getNode(int id) throws GraphException;
                    /* Returns the node with the specified id. Throws a 
		       GraphException if the node does not exist. */

  public Iterator incidentEdges(Node u) throws GraphException;
                    /* Returns a Java Iterator storing all the edges incident
		       on the specified node. It returns null if the node does
		       not have any edges incident on it. Throws a GraphException
		       if the node does not exist. */

  public Edge getEdge(Node u, Node v) throws GraphException;
                    /* Returns the edge connecting the given nodes. Throws 
		       a GraphException if there is no edge conencting the given 
		       nodes, or if u or v do not exist. */

  public boolean areAdjacent(Node u, Node v) throws GraphException;
                   /* Returns true is u and v are adjacent, and false otherwise. 
		      It throws a GraphException if either node does not exist. */
 
}