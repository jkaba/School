/**
 * CS2210A Assignment 5 
 * @author Jameel Kaba (jkaba) Student #: 250796017
 * 
 * Edge class that represents the edge of a graph
 */
public class Edge {

	// Private variables
	private Node edgeU;
	private Node edgeV;
	private String edgeBusLine;

	/**
	 * Constructor method that creates an edge with 2 endpoints and a busline associated
	 * with the street represented by the edge passed as parameters
	 * @param u Node that represents First endpoint
	 * @param v Node that represents Second endpoint
	 * @param busLine String that represents the busline that is associated with the edge
	 */
	public Edge(Node u, Node v, String busLine) {
		edgeU = u;
		edgeV = v;
		edgeBusLine = busLine;
	}

	/**
	 * Getter method that returns the first end point of the edge
	 * @return The first end point of the edge
	 */
	public Node firstEndpoint() {
		return edgeU;
	}

	/**
	 * Getter method that returns the second end point of the edge
	 * @return The second end point of the edge
	 */
	public Node secondEndpoint() {
		return edgeV;
	}

	/**
	 * Getter method that gets the busline to which the edge belongs
	 * @return The busline associated with the edge
	 */
	public String getBusLine() {
		return edgeBusLine;
	}


}
