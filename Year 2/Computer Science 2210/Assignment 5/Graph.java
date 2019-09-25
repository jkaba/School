/**
 * CS2210A Assignment 5 
 * @author Jameel Kaba (jkaba) Student #: 250796017
 *
 * This class represents an undirected graph using an
 * adjacency matrix representation for the graph
 */

import java.util.*;

public class Graph {

	// Private variables
	private Node nodes[];	
	private Edge edges[][];	

	/**
	 * Constructor that creates a graph with n nodes 
	 * and no edges
	 * @param n The number of nodes in the graph
	 */
	public Graph(int n){

		// Create an array for the nodes and edges
		nodes = new Node[n];
		edges = new Edge[n][n];

		for (int i=0; i < n; i++){
			// Create a node at position i of the node array with 
			// a node whose name is that of which i is
			nodes[i] = new Node(i);
		}

	}

	/**
	 * Insert Edge method that adds an edge connecting nodes u and v and 
	 * belong to a specified bus line
	 * @param u The first end point of the edge
	 * @param v The second end point of the edge
	 * @param busLine The busline that the edge belongs to
	 * @throws GraphException thrown if the either node exists or
	 * if the edge is already in the graph
	 */
	public void insertEdge(Node u, Node v, String busLine) throws GraphException{

		// If the nodes are valid
		if (u.getName()>=0 && v.getName()>=0 && u.getName()<nodes.length && v.getName()<nodes.length){

			// check to see if there is no edge between them
			if (edges[u.getName()][v.getName()] == null && edges[v.getName()][u.getName()] == null){

				// form the edges to be inserted
				edges[u.getName()][v.getName()] = new Edge(u, v, busLine);
				edges[v.getName()][u.getName()] = new Edge(v, u, busLine);
			}
			else
				// if an edge exists throw an exception
				throw new GraphException("ERROR 404: Edge already exists");
		}
		else
			// if a node is invalid throw an exception
			throw new GraphException("ERROR 404: invalid node");
	}

	/**
	 * Get Node method that gets the node with a specified name
	 * @param name The name of the node to be found
	 * @return the Node in the position of it's name
	 * @throws GraphException if the node does not exist
	 */
	public Node getNode(int name) throws GraphException{

		// if the name of the node is valid
		if (name>=0 && name<nodes.length)

			// return the node
			return nodes[name];
		else
			// throw an exception if the node is invalid
			throw new GraphException("Invalid node");
	}

	/**
	 * incidentEdges method that gets an iterator that
	 * stores all the edges incident on node u
	 * @param u The node whose incident edges we're looking for
	 * @return an iterator with the incident edges or null if the
	 * node does not have any edges incident to it
	 * @throws GraphException if the node is invalid
	 */
	public Iterator<Edge> incidentEdges(Node u) throws GraphException{

		// if the node is valid
		if (u.getName() >= 0 && u.getName() < nodes.length){

			// create a stack of edges
			Stack<Edge> incidentEdges = new Stack<Edge>();

			// for every edge in the graph that are incident on u
			for (int i = 0; i < nodes.length; i++){
				if (edges[u.getName()][i] != null){

					// push that edge into the stack
					incidentEdges.push(edges[u.getName()][i]);
				}
			}
			// if the stack is empty
			if (incidentEdges.isEmpty()){
				// return null
				return null;
			}
			else{
				// else return the iterator for the stack
				return incidentEdges.iterator();
			}
		}
		else
			// throw an exception if a node is invalid
			throw new GraphException("Invalid node");
	}

	/**
	 * getEdge method that gets the edge that connects 
	 * two specified nodes
	 * @param u the first end point of the edge
	 * @param v the second end point of the edge
	 * @return the edge connecting u and v or null if 
	 * no such edge exists
	 * @throws GraphException if there is no such edge connecting
	 * the two nodes or if one of the nodes is invalid
	 */
	public Edge getEdge(Node u, Node v) throws GraphException{

		// if the nodes are valid
		if (u.getName()>=0 && v.getName()>=0 && u.getName()<nodes.length && v.getName()<nodes.length){

			// check to see if there is an edge between them
			if (edges[u.getName()][v.getName()] == null){

				// if not throw an exception
				throw new GraphException("No edge between specified nodes");
			}
			else{
				// if there is return the edge
				return edges[u.getName()][v.getName()];
			}
		}

		else{
			// throw an exception if one of the nodes are invalid
			throw new GraphException("Invalid node");
		}
	}

	/**
	 * are Adjacent method that returns true if two specified nodes 
	 * are adjacent 
	 * @param u first node
	 * @param v second node
	 * @return true if the two nodes are adjacent false otherwise
	 * @throws GraphException if one of the nodes are invalid
	 */
	public boolean areAdjacent(Node u, Node v) throws GraphException{

		// if the nodes are valid
		if (u.getName()>=0 && v.getName()>=0 && u.getName()<nodes.length && v.getName()<nodes.length)

			// if the edge exists between them
			if(edges[u.getName()][v.getName()] != null){
				// return true
				return true;
			}

			else{
				// else return false
				return false;
			}

		else
			// throw an exception if a node is invalid
			throw new GraphException("Invalid node");
	}
}