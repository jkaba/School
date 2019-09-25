import java.util.Iterator;

public interface GraphADT {

  public void insertEdge(Node nodeu, Node nodev, String busLine) 
                                              throws GraphException;
                    /* Adds to the graph an edge connecting the given vertices.
                       The type of the edge is as indicated. Throws a GraphException
		       if either node does not exist or if the edge is already 
		       in the graph.*/

  public Node getNode(int name) throws GraphException;
                    /* Returns the node with the specified name. Throws a 
		       GraphException if the node does not exist. */

  public Iterator incidentEdges(Node u) throws GraphException;
                    /* Returns a Java Iterator storing all the edges incident
		       on the specified node. It returns null if the node does
		       not have any edges incident on it. Throws a GraphException
		       if the node does not exist. */

  public Edge getEdge(Node u, Node v) throws GraphException;
                    /* Returns the edge connecting the given vertices. Throws 
		       a GraphException if there is no edge conencting the given 
		       vertices or if u or v do not exist. */

  public boolean areAdjacent(Node u, Node v) throws GraphException;
                   /* Returns true is u and v are adjacent, and false otherwise. 
		      It throws a GraphException if either vertex does not 
		      exist. */
 
}
